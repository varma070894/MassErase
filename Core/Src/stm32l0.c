#include "stm32l0.h"
#include "libswd.h"

extern int32_t Counter;

int32_t STM32L0_set_bits(libswd_ctx_t *libswdctx, uint32_t addr, uint32_t bits)
{
    uint32_t value;
    // Read memory address
    int32_t retval = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, 1, (int*)&value);
    if (retval < 0)
    {
        return retval;        
    }
    // Set bits
    value |= bits; 
    // Write the resulting value back
    return libswd_memap_write_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, 1, (int*)&value);
}

int32_t STM32L0_clear_bits(libswd_ctx_t *libswdctx, uint32_t addr, uint32_t bits)
{
    uint32_t value;
    // Read memory address
    int32_t retval = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, 1, (int*)&value);
    if (retval < 0)
    {
        return retval;        
    }
    // Clear bits
    value &= ~bits; 
    // Write the resulting value back
    return libswd_memap_write_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, 1, (int*)&value);
}

int32_t STM32L0_wait_busy(libswd_ctx_t *libswdctx)
{
    int32_t i;
    uint32_t sr;
    // Wait until the BSY bit is reset in the FLASH_SR register
    for (i = LIBSWD_RETRY_COUNT_DEFAULT; i ; i--)
    {
        int32_t retval = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
        if (retval < 0) return retval;        
        
        if (!(sr & STM32L0_FLASH_SR_BSY))
        {
            return LIBSWD_OK;
        }
        Delay(1000);
    }
    return LIBSWD_ERROR_MAXRETRY;
}


int32_t STM32L0_option_byte_write(libswd_ctx_t *libswdctx, uint32_t addr, uint32_t data)
{
    // Write a 32-bit word value at the option byte address,
    //uint32_t data = (uint32_t)((~data << 16) | data);
    int32_t retval = libswd_memap_write_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, 1, (int*)&data);
    if (retval < 0) 
    {
        return retval;
    }
    
    // Wait until the BSY bit is reset in the FLASH_SR register
    retval = STM32L0_wait_busy(libswdctx);
    if (retval < 0) return retval;        

    uint32_t sr;
    // Check the EOP flag in the FLASH_SR register
    retval = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
    if (retval < 0) return retval;        
 
    if ((sr & STM32L0_FLASH_SR_EOP) != 0) 
    {
        // Clear EOP flag by software by writing EOP at 1 
        data = STM32L0_FLASH_SR_EOP;
        return libswd_memap_write_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&data);
    } 
    else
    {
        return -102;
    }
}

int32_t STM32L0_option_byte_prog(libswd_ctx_t *libswdctx, uint32_t addr, uint16_t data)
{
    // Write a 32-bit word value at the option byte address,
    uint32_t data32 = (uint32_t)((~data << 16) | data);
    return STM32L0_option_byte_write(libswdctx, addr, data32);
}

int32_t STM32L0_option_byte_erase(libswd_ctx_t *libswdctx, uint32_t addr)
{
    // Set the ERASE bit in the FLASH_PECR register to enable option byte erasing 
    int32_t retval = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_ERASE);
    if (retval < 0)
    {
        return retval;        
    }

    retval = STM32L0_option_byte_write(libswdctx, 0x1FF80000, 0xFFFF0000);
    if (retval < 0) 
    {
        return retval;
    }
    
    // Reset the ERASE and PROG bits in the FLASH_PECR register to disable the page erase
    return STM32L0_clear_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_ERASE);
}




int32_t STM32L0_unlock_nvm(libswd_ctx_t *libswdctx)
{
    // Wait until the BSY bit is reset in the FLASH_SR register
    int32_t ret = STM32L0_wait_busy(libswdctx);
    if (ret < 0) return ret;  

    uint32_t pecr;
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
    if (ret < 0) return ret;        
    
    if ((pecr & STM32L0_FLASH_PECR_PELOCK) != 0) 
    {
        
        ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                            STM32L0_FLASH_PEKEYR_ADDR, STM32L0_FLASH_PEKEYR_KEY1);
        if (ret < 0) return ret;        
        
        return libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                             STM32L0_FLASH_PEKEYR_ADDR, STM32L0_FLASH_PEKEYR_KEY2);
    }
    return LIBSWD_OK;
}


int32_t STM32L0_unlock_opt(libswd_ctx_t *libswdctx)
{
    // Wait until the BSY bit is reset in the FLASH_SR register
    int32_t ret = STM32L0_wait_busy(libswdctx);
    if (ret < 0) return ret;  

    uint32_t pecr;
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
    if (ret < 0) return ret;        
    
    if ((pecr & STM32L0_FLASH_PECR_PELOCK) == 0) 
    {
        if ((pecr & STM32L0_FLASH_PECR_OPTLOCK) != 0) 
        {
            // unlock options
            ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                            STM32L0_FLASH_OPTKEYR_ADDR, STM32L0_FLASH_OPTKEYR_KEY1);
            if (ret < 0) return ret;        
        
            ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                            STM32L0_FLASH_OPTKEYR_ADDR, STM32L0_FLASH_OPTKEYR_KEY2);
            if (ret < 0) return ret;        
            
            // check unlock state
            ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
            if (ret < 0) return ret;  
            
            if ((pecr & STM32L0_FLASH_PECR_OPTLOCK) != 0) 
            {
                // unlock failed
                return -109;
            }
        }
        return LIBSWD_OK;
    }
    return -105;
}


int32_t STM32L0_unlock_prog(libswd_ctx_t *libswdctx)
{
    // Wait until the BSY bit is reset in the FLASH_SR register
    int32_t ret = STM32L0_wait_busy(libswdctx);
    if (ret < 0) return ret;  

    uint32_t pecr;
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
    if (ret < 0) return ret;        
    
    if ((pecr & STM32L0_FLASH_PECR_PELOCK) == 0) 
    {
        if ((pecr & STM32L0_FLASH_PECR_PRGLOCK) != 0) 
        {
            // unlock programming
            ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                            STM32L0_FLASH_PRGKEYR_ADDR, STM32L0_FLASH_PRGKEYR_KEY1);
            if (ret < 0) return ret;        
        
            ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                            STM32L0_FLASH_PRGKEYR_ADDR, STM32L0_FLASH_PRGKEYR_KEY2);
            if (ret < 0) return ret;    
            
            // check unlock state
            ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
            if (ret < 0) return ret;  
            
            if ((pecr & STM32L0_FLASH_PECR_PRGLOCK) != 0) 
            {
                // unlock failed
                return -109;
            }
        }
        return LIBSWD_OK;
    }
    return -105;
}



int32_t STM32L0_mass_erase(libswd_ctx_t *libswdctx)
{
    uint32_t optr, sr;

    int ret = STM32L0_unlock_nvm(libswdctx);
    if (ret < 0) return ret;
    ret = STM32L0_unlock_opt(libswdctx);
    if (ret < 0) return ret;
    
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
    if (ret < 0) return ret;   
    
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_OPTR_ADDR, 1, (int*)&optr);
    if (ret < 0) return ret;
    
    if ((optr & 0x000000FF) == 0xCC)
    {
        // Device locked to level 2, not possible to program/erase
        return -100;
    }
    else if ((optr & 0x000000FF) == 0xAA)
    {
        ret = STM32L0_option_byte_erase(libswdctx, 0x1FF80000);
        if (ret < 0) return ret;
        // The MCU will reset while executing the option bytes reloading

        ret = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_OBL_LAUNCH);
                   if (ret < 0) return ret;
        Delay(40000);
        return 42;
    }

    ret = STM32L0_option_byte_prog(libswdctx,0x1FF80000, 0x00AA);
    if (ret < 0) 
    {
        return ret;
    }
//Mass erase operation takes atleast 30s
    Delay(1000000);
    return 0;
}

int32_t STM32L0_ReadOut_Lock(libswd_ctx_t *libswdctx)
{
    uint32_t optr, sr;

    int ret = STM32L0_unlock_nvm(libswdctx);
    if (ret < 0) return ret;
    ret = STM32L0_unlock_opt(libswdctx);
    if (ret < 0) return ret;

    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
    if (ret < 0) return ret;

    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_OPTR_ADDR, 1, (int*)&optr);
    if (ret < 0) return ret;

    if ((optr & 0x000000FF) == 0xCC)
    {
        // Device locked to level 2, not possible to program/erase
        return -100;
    }
    else if ((optr & 0x000000FF) == 0xAA)
    {
    	//Level 1 is set by assigning a value other than 0xAA and 0xCC to first word of option byte
    	//I have assigned Zeros in [15:0] and its compliment in [31:16]
    	int retval = STM32L0_option_byte_write(libswdctx, 0x1FF80000, 0xFFFF0000);
    	    if (retval < 0)
    	    {
    	        return retval;
    	    }
       ret = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_OBL_LAUNCH);
    	                      if (ret < 0) return ret;
       Delay(40000);

    }
    return 0;
}


int32_t STM32L0_half_page_prog(libswd_ctx_t *libswdctx, uint32_t *data, uint32_t addr, uint32_t half_page_size)
{
   int ret = libswd_memap_write_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, addr, half_page_size / 4, (int*)data);
    if (ret < 0) return ret;        
    
    // Wait until the BSY bit is reset in the FLASH_SR register
    ret = STM32L0_wait_busy(libswdctx);
    if (ret < 0) return ret;        

    uint32_t sr;
    // Check the EOP flag in the FLASH_SR register
    ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
    if (ret < 0) return ret;        
 
    if ((sr & STM32L0_FLASH_SR_EOP) != 0)
    {
        // Clear EOP flag by software by writing EOP at 1 
        ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE, 
                                             STM32L0_FLASH_SR_ADDR, STM32L0_FLASH_SR_EOP);
        if (ret < 0) return ret; 
    } 
    else
    {
        return -102;
    }

   return 0;
}



int32_t STM32L0_prog(libswd_ctx_t *libswdctx, uint8_t *data, uint32_t count, uint32_t addr, uint32_t page_size)
{
    int ret = STM32L0_unlock_nvm(libswdctx);
    if (ret < 0) return ret;
    ret = STM32L0_unlock_prog(libswdctx);
    if (ret < 0) return ret;

    uint32_t sr, pecr;
       // Check the EOP flag in the FLASH_SR register
       ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_SR_ADDR, 1, (int*)&sr);
       if (ret < 0) return ret;

        ret = libswd_memap_read_int_32(libswdctx, LIBSWD_OPERATION_EXECUTE, STM32L0_FLASH_PECR_ADDR, 1, (int*)&pecr);
       if (ret < 0) return ret;

       // Set the PROG and FPRG bits in the FLASH_PECR register to enable a half page programming
        ret = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR,
                                         STM32L0_FLASH_PECR_PROG | STM32L0_FLASH_PECR_FPRG);
       if (ret < 0) return ret;

    for (uint32_t i = 0; i < count; i+= page_size / 2)
    {
        ret = STM32L0_half_page_prog(libswdctx, (uint32_t*)data, addr, page_size / 2);
        if (ret < 0) return ret;
        addr += page_size / 2;
        data += page_size / 2;
    }
    // Reset the ERASE and PROG bits in the FLASH_PECR register to disable the page erase
        ret = STM32L0_clear_bits(libswdctx, STM32L0_FLASH_PECR_ADDR,
                                  STM32L0_FLASH_PECR_PROG | STM32L0_FLASH_PECR_FPRG);
        if (ret < 0) return ret;
        ret = libswd_memap_write_int_32_val(libswdctx, LIBSWD_OPERATION_EXECUTE,
                                                     STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_PELOCK);
                if (ret < 0) return ret;
        return 0;
}
    
 
extern const char program1[6496];
extern const char program2[6496];

int32_t STM32L0_main(void)
{
    libswd_ctx_t *libswdctx = libswd_init();
    int32_t retval;
    
    // Check if target is halted, halt if necessary.
    if (!libswd_debug_is_halted(libswdctx, LIBSWD_OPERATION_EXECUTE))
    {
        retval = libswd_debug_halt(libswdctx, LIBSWD_OPERATION_EXECUTE);
        if (retval < 0) return -101;
    }

      if(Counter % 2 == 0)
    {
    retval = STM32L0_mass_erase(libswdctx);
    if (retval == 42)
       	    {
       	        // MCU reset performed, reinit SWD
       	        libswd_deinit(libswdctx);
       	        libswdctx = libswd_init();

       	        if (!libswd_debug_is_halted(libswdctx, LIBSWD_OPERATION_EXECUTE))
       	        {
       	            retval = libswd_debug_halt(libswdctx, LIBSWD_OPERATION_EXECUTE);
       	            if (retval < 0) return -101;
       	        }
       	        retval = STM32L0_mass_erase(libswdctx);
       	        if (retval < 0) return -102;
       	    }
    //Delay(50000);
    // The MCU will reset while executing the option bytes reloading
   int ret = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_OBL_LAUNCH);
                       if (ret < 0) return ret;
                       libswd_deinit(libswdctx);
    libswdctx = libswd_init();
    if (!libswd_debug_is_halted(libswdctx, LIBSWD_OPERATION_EXECUTE))
    	          	        {
    	          	            retval = libswd_debug_halt(libswdctx, LIBSWD_OPERATION_EXECUTE);
    	          	            if (retval < 0) return -101;
    	          	        }
    STM32L0_prog(libswdctx, (uint8_t*)program2, sizeof(program2), 0x08000000, 128);
    //changing to Level1 for Readout Protection
    STM32L0_ReadOut_Lock(libswdctx);
    }
   else
   {
	   retval = STM32L0_mass_erase(libswdctx);
	       if (retval == 42)
	          	    {
	          	        // MCU reset performed, reinit SWD
	          	        libswd_deinit(libswdctx);
	          	        libswdctx = libswd_init();

	          	        if (!libswd_debug_is_halted(libswdctx, LIBSWD_OPERATION_EXECUTE))
	          	        {
	          	            retval = libswd_debug_halt(libswdctx, LIBSWD_OPERATION_EXECUTE);
	          	            if (retval < 0) return -101;
	          	        }
	          	        retval = STM32L0_mass_erase(libswdctx);
	          	        if (retval < 0) return -102;
	          	    }
	      // Delay(50000);
	       // The MCU will reset while executing the option bytes reloading
	      int ret = STM32L0_set_bits(libswdctx, STM32L0_FLASH_PECR_ADDR, STM32L0_FLASH_PECR_OBL_LAUNCH);
	                          if (ret < 0) return ret;
	                          libswd_deinit(libswdctx);
	       libswdctx = libswd_init();
	       if (!libswd_debug_is_halted(libswdctx, LIBSWD_OPERATION_EXECUTE))
	       	          	        {
	       	          	            retval = libswd_debug_halt(libswdctx, LIBSWD_OPERATION_EXECUTE);
	       	          	            if (retval < 0) return -101;
	       	          	        }
   	STM32L0_prog(libswdctx, (uint8_t*)program1, sizeof(program1), 0x08000000, 128);
    //Changing to Level1 for Readout Protection
    STM32L0_ReadOut_Lock(libswdctx);
   }
    
    libswd_deinit(libswdctx);
    return 0;
}
