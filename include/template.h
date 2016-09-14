#ifndef TEMPLATE_H
#define TEMPLATE_H

#include "list.h"

typedef struct Templste {
	char *filename;

	ListNode *context;
} Template;


Template *templateConstructor(char *);
void templateDel(Template *);
void templateSet(Template *, char *, char *);
char *templateRender(Template *);

#endif
