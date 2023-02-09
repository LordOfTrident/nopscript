#include "token.h"

void token_free(token_t *tok) {
	if (tok->data != NULL) {
		free(tok->data);
		tok->data = NULL;
	}
}

static const char *token_type_to_cstr_map[] = {
	[TOKEN_TYPE_EOF] = "end of file",

	[TOKEN_TYPE_ID]  = "identifier",
	[TOKEN_TYPE_STR] = "string",
	[TOKEN_TYPE_DEC] = "decimal number",

	[TOKEN_TYPE_TRUE]  = "true",
	[TOKEN_TYPE_FALSE] = "false",
	[TOKEN_TYPE_LET]   = "let",

	[TOKEN_TYPE_ADD] = "+",
	[TOKEN_TYPE_SUB] = "-",
	[TOKEN_TYPE_MUL] = "*",
	[TOKEN_TYPE_DIV] = "/",
	[TOKEN_TYPE_POW] = "^",

	[TOKEN_TYPE_ASSIGN]      = "=",
	[TOKEN_TYPE_EQUALS]      = "==",
	[TOKEN_TYPE_NOT_EQUALS]  = "/=",
	[TOKEN_TYPE_GREATER]     = ">",
	[TOKEN_TYPE_GREATER_EQU] = ">=",
	[TOKEN_TYPE_LESS]        = "<",
	[TOKEN_TYPE_LESS_EQU]    = "<=",

	[TOKEN_TYPE_LPAREN] = "(",
	[TOKEN_TYPE_RPAREN] = ")",
	[TOKEN_TYPE_COMMA]  = ",",

	[TOKEN_TYPE_ERR] = "error",
};

static_assert(TOKEN_TYPE_COUNT == 23); /* Add the new token type to the map */

const char *token_type_to_cstr(token_type_t type) {
	if (type >= TOKEN_TYPE_COUNT)
		UNREACHABLE("Invalid token type");

	return token_type_to_cstr_map[type];
}

token_t token_new(char *data, token_type_t type, where_t where) {
	return (token_t){
		.data  = data,
		.type  = type,
		.where = where,
	};
}

token_t token_new_eof(where_t where) {
	return token_new(NULL, TOKEN_TYPE_EOF, where);
}

token_t token_new_err(char *msg, where_t where) {
	return token_new(msg, TOKEN_TYPE_ERR, where);
}
