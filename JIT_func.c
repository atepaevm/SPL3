#include "JIT_func.h"


char* strcopy(char* dest, char* scr, int len){
    for(int i = 0; i < len; i++){
        *(dest++)=*(scr++);
    }
    return dest;
}


void* replace(void *func, int *mass, int len){
	/*
	 * Данная функция принимает указатель на функцию, массив чисел и длину этого массива ...
	 * ... возвращаемым значением функции является указатель на функцию, которая возвращает...
	 * ... int и принимает количество параметров, равное количеству параметров исходной функции ...
	 * ... за вычетом тех, которые были переданы. Пока что тип принимаемого\возвращаемого ...
	 * ... значения - int, а количество параметров ограничено шестью.
	 */
    char const_regs[regc] = {0xbf, 0xbe, 0xba, 0xb9, 0xb8, 0xb9};
    /* массив, использующий odcode'ы операций при обращениям ...
     *  ... к регистрам при записи в них константных значений*/
    const char mov = 0x89, mvr_re = 0x44, mvre_r = 0x41;
    char regs_rax[regc] = {0xf8, 0xf0, 0xd0, 0xc8, 0xc0, 0xc8};
    char rax_regs[regc] = {0xc7, 0xc6, 0xc2, 0xc1, 0xc0, 0xc1};
    /* массив, использующий odcode'ы операций при обращениям ...
     *  ...  к регистрам (запись из\в) при работе с регистром rax*/

    char *num,*beg, *function = (char*)mmap(NULL, 150, PROT_WRITE|PROT_EXEC, MAP_SHARED|MAP_ANONYMOUS, -1, 0);
    int i = 0;
    beg = function;
    for(i = regc-len-1; i >= 0; i--){
    	/* Сначала - сдвигаем параметры, которые не являются константами, в конец */
    	if(i > 3){
    		*(function++)= mvre_r;
    	}
    	*(function++)= mov;
    	*(function++)= regs_rax[i];
    	if(i > 3){
    		*(function++)= mvr_re;
    	}
    	*(function++)= mov;
    	*(function++)= rax_regs[len + i];
    }

    i = 0;
    while(i < len){
    	/*
    	 * Запись констант в перечисленные регистры, через которые они передаются в функцию.
    	 */
    	if(i > 3){
    		*(function++)= mvre_r;
    	}
    	*(function++)= const_regs[i];
        function = strcopy(function, num = int_to_LEstr(mass[i]), 4);
        free(num);
        i++;
    }

    *(function++) = 0x48; /*mov from memory*/
    *(function++) = 0xb8; /*запись значения из памяти в регистр rax*/
    function = strcopy(function, num = int_to_LEstr((int)func), 8);
    *(function++) = 0xff; /*jmp по абсолютному адресу (jmpq) ...*/
    *(function++) = 0xe0; /*...для регистра rax*/
    return beg;
}

char* int_to_LEstr(int a){
    char *buf,*str = calloc(4, sizeof(char));
    buf = str;
    while(a != 0){
        *(str++) = a % 256;
        a /= 256;
    }
    return buf;
}
