#ifdef HAVE_CONFIG_H
#include <config.h>
#endif
#ifdef HAVE_STRING_H
#include <string.h>
#else
#include <strings.h>
#endif

#include "internal.h"
#include "die.h"
#include "strbuf.h"
/* "strlimcpy.h" */
#include "token.h"
#include "vb_res.h"

void
vb(const struct parser_param *param)
{
	int c;
	int level;					/* brace level */
	const char *interested = NULL;

	if (!opentoken(param->file))
		die("'%s' cannot open.", param->file);
	while ((c = nexttoken(interested, vb_reserved_word)) != EOF) {
		switch (c) {
		case SYMBOL:
			PUT(PARSER_REF_SYM, token, lineno, sp);
			break;
		case VB_CLASS:
		case VB_MODULE:
		case VB_FUNCTION:
		case VB_SUB:
			if ((c = nexttoken(interested, vb_reserved_word)) == SYMBOL) {
				PUT(PARSER_DEF, token, lineno, sp);
			}
			break;
		default:
			break;
		}
	}
	closetoken();
}
