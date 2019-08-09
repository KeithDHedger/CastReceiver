/******************************************************
*
*     ©keithhedger Mon  5 Aug 20:25:10 BST 2019
*     kdhedger68713@gmail.com
*
*     common.cpp
* 
******************************************************/

#include "common.h"

bool	exitOnStop=false;

struct xmlelement *gen_specversion(struct xmldoc *doc,int major,int minor)
{
	struct xmlelement *top;

	top=xmlelement_new(doc,"specVersion");

	add_value_element_int(doc,top,"major",major);
	add_value_element_int(doc,top,"minor",minor);

	return(top);
}
