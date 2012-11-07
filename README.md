stringbuf
=========

Efficient ref garbage collected string buffer in C.

A string buffer is necessary when generating text files from C.

Two methods:

    <buf> stringbuf_New(<capacity>)
    
    stringbuf_Append(<buf>, <string>)
    
The size is doubled each time it expands.

