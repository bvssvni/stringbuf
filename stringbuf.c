
#include <stdlib.h>
#include <string.h>

#include "ref.h"
#include "stringbuf.h"

stringbuf_t *stringbuf_New(int capacity)
{
	// Do not start with no capacity.
	if (capacity <= 0) capacity = 1;
	
	gcInit(stringbuf_t, buf,
		   .cap = capacity,
		   .ptr = malloc(capacity * sizeof(char)));
	memset(buf->ptr, 0, buf->cap * sizeof(char));
	return buf;
}

void stringbuf_Delete(stringbuf_t *buf)
{
	if (buf == NULL) return;
	
	// Release buffer if this is the last reference.
	if (!buf->ref.keep) {
		free(buf->ptr);
		buf->ptr = NULL;
	}
}

void stringbuf_Append(stringbuf_t *buf, const char *text)
{
	if (buf == NULL) return;
	if (buf->ptr == NULL) return;
	
	int length = strlen(text);
	int mem = buf->cap - buf->len - 1;
	
	if (mem < length) {
		// Double until it got room for the text.
		int expand = buf->cap;
		while (expand < length + buf->len + 1) {
			expand <<= 1;
		}
		
		// Create new buffer.
		char *arr = malloc(expand * sizeof(char));
		memset(arr, 0, expand * sizeof(char));
		
		// Copy data from old buffer into new.
		memcpy(arr, buf->ptr, buf->cap);
		
		// Release old buffer.
		free(buf->ptr);
		
		// Replace with new buffer.
		buf->ptr = arr;
		buf->cap = expand;
	}
	
	memcpy(buf->ptr + buf->len, text, length * sizeof(char));
	buf->len += length;
}

