#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "ref.h"
#include "stringbuf.h"

#define func(ns, name) static __typeof__(ns##_##name) * const name = ns##_##name

func(stringbuf, New);
func(stringbuf, Append);

// 2^25 in 5.792s
void test_stringbuf_1(void)
{
	stringbuf_t *buf = New(100);
	
	gcSet(buf, NULL);
}

// 2^24 in 8.325s
void test_stringbuf_2(void)
{
	stringbuf_t *buf = New(0);
	
	assert(buf->cap == 1);
	
	Append(buf, "hello");
	
	assert(buf->len == 5);
	assert(buf->cap == 8);
	
	Append(buf, " ");
	
	assert(buf->len == 6);
	assert(buf->cap == 8);
	
	Append(buf, "Sven");
	
	assert(buf->len == 10);
	assert(buf->cap == 16);
	
	// printf("%s\n", buf->ptr);
	
	gcSet(buf, NULL);
}

void test_stringbuf_3(void)
{
	stringbuf_t *a = New(0);
	stringbuf_t *b = NULL;
	
	gcSet(b, a);
	gcSet(a, NULL);
	gcSet(b, NULL);
}

// 2^25 in 11.852s
void test_stringbuf_4(void)
{
	stringbuf_t *a = New(0);
	stringbuf_t *b = New(0);
	
	// Use garbage collector.
	gcStart(gcRef(a), gcRef(b));
	
	gcSet(b, a);
	
	assert(b == a);
	
	// Clean up.
	gcEnd();
}

void test_stringbuf_5(void)
{
	stringbuf_t *a = New(100);
	stringbuf_t *b = New(100);
	
	gcStart(gcRef(a), gcRef(b));
	
	gcCopy(a, b);
	a->ptr = NULL;
	
	gcEnd();
}

int main(int argc, char *argv[])
{
	test_stringbuf_1();
	test_stringbuf_2();
	test_stringbuf_3();
	test_stringbuf_4();
	
	/*/
	int i;
	int end = 1 << 25;
	for (i = 0; i < end; i++) {
		test_stringbuf_4();
	}
	//*/
	
	return 0;
}