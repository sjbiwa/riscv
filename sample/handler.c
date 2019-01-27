/*
 * handler.c
 *
 */
extern void (**__init_array_start)();
extern void (**__init_array_end)();
 
char buff[1024];

void static_init()
{
  for (void (**p)() = __init_array_start; p < __init_array_end; ++p)
    (*p)();
}



