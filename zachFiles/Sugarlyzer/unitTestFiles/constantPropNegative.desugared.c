#include <stdbool.h>

extern void __static_parse_error(char *msg);
extern void __static_type_error(char *msg);
extern void __static_renaming(char *renaming, char *original);
extern void __static_condition_renaming(char *expression, char *renaming);

void __static_initializer_default();

extern const bool __static_condition_default_7;
extern const bool __static_condition_default_9;
extern const bool __static_condition_default_8;
extern const bool __static_condition_default_10;
extern const bool __static_condition_default_6;
extern const bool __static_condition_default_5;
void __static_initializer_default() {
__static_renaming("__read_0", "read");
__static_renaming("__x_1", "x");
__static_renaming("__y_2", "y");
__static_renaming("__z_3", "z");
__static_renaming("__main_4", "main");

__static_condition_renaming("__static_condition_default_5", "(defined READ_X)");
__static_condition_renaming("__static_condition_default_6", "!(defined READ_X)");
__static_condition_renaming("__static_condition_default_7", "(defined INC)");
__static_condition_renaming("__static_condition_default_8", "!(defined INC)");
__static_condition_renaming("__static_condition_default_9", "(defined READ_X)");
__static_condition_renaming("__static_condition_default_10", "!(defined READ_X)");

};

extern void  (__read_0) (void  *);// L1
int  (__main_4) () {

{
{



int  __x_1;// L3

int  __y_2;// L4

int  __z_3;// L5

if (__static_condition_default_5) {
 __read_0  (&  __x_1 ) ; // L7
}
if (__static_condition_default_6) {
 __x_1  = 4 ; // L9
}
 __read_0  (&  __y_2 ) ; // L11
 __read_0  (&  __z_3 ) ; // L12
if (__static_condition_default_7) {
 __x_1  =  __x_1  + 4 ; // L14
}
if (__static_condition_default_8) {
 __y_2  =  __y_2  +  __x_1  ; // L16
}
if (__static_condition_default_7) {
 __y_2  =  __y_2  +  __x_1  ; // L16
}
if (  __y_2  >  __z_3  )// L17
{

{
{



return 2 ;// L18
}
}
}
else
{
if (__static_condition_default_9) {

{
{



return 1 ;// L25
}
}
}
if (__static_condition_default_10) {

{
{



if (  __x_1  > 3 )// L21
{

{
{



return 1 ;// L22
}
}
}
}
}
}
}
return 0 ;// L28
}
}


}

