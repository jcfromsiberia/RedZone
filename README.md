RedZone
=======

RedZone is a lightweight C++ template engine with Jinja2-like syntax support.
Inspired by [microtemplates](https://github.com/alexmic/microtemplates).
This is the starting point for other languanges extensions (e.g. Python).
Data exchange is provided via JSON protocol.

## Build

To build RedZone library you should have installed GCC 4.9 as well as CMake tool.
Execute this shell script:
``` sh
$ git clone https://github.com/jcfromsiberia/RedZone && cd RedZone && mkdir build && cd build && cmake .. && make
```

### Building Python extension
You'll need the same tools with Python dev package and Cython.
Use `-DBUILD_LANG_EXTENSION=python` flag for cmake command:
``` sh
$ cmake -DBUILD_LANG_EXTENSION=python .. && make
```
You'll find built RedZone.so python module in the build dir.

## How to use?

There are equivalent examples for C++ and Python.
- [main.cpp](main.cpp)
- [test.py](cython/test.py)

Link RedZone library to your application or library and use these following classes inside:

#### RedZone::Writer
This is an abstract class for output. It has only two pure virtual methods
- void write( std::string const & data )
- void flush()

There are obly two classes which implement this abstract class:
##### RedZone::FileWriter
Writes string data to file on disk. Constructor accepts a path to output file.

``` cpp
RedZone::FileWriter writer( "/tmp/out.html" );
```

##### RedZone::StringWriter
Writes string data to in-memory string. Constructor accepts a reference to certain string.
``` cpp
std::string out;
RedZone::FileWriter writer( out );
```


#### RedZone::Template and its derived ones
There is only one working class `RedZone::FileTemplate` to load a template from filesystem by path for the time being.
``` cpp
RedZone::FileTemplate tpl( "/tmp/test.tpl" );
```
This code creates reads file contents from the given path (e.g. `/tmp/test.tpl`), parses it and then creates a new `RedZone::Template` instance.

#### json11::Json
RedZone uses JSON protocol for storing the rendering context. To implement JSON protocol, I have used [json11](https://github.com/dropbox/json11).
``` cpp
json11::Json json( json11::Json::parse( R"(
      {                                               
         "items": [                                   
           { "text": "Hello World!", "active": true },
           { "text": "Foo", "active": true },         
           { "text": "Bar", "active": false }         
         ],
         "numbers": {
            "first": 5,
            "second": 11,
            "third": true
         }  
      }                                               
       )", err ) );
```

#### RedZone::Context
Rendering context accepts json object-type instances only. You can not pass arrays or something else.
`RedZone::Template` classes have `render` method to render the template with user context into a `stream` represented as pointer to `Writer` isntance.
``` cpp
RedZone::Context context( json ); 
tpl.renderToStream( &writer, &context);
context.setJson( anotherJson );
```

Also they have `render` method, which returns complete rendered output. It uses `StringWriter` inside.
``` cpp
std::string rendered = tpl.render( &context );
```

RedZone supports a primitive code evaluation support. It supports main expression operations like:

1. math expressions;
2. function calls;
3. string operations;
4. comparison operations.

You can use them in variable blocks; as bool condition in 'if' block; as container expression in for block.

So, having this markup in `/tmp/test.tpl`:
```
{% for item in items %}
    {% if item.active && length(item.text) == 3 %}
	<div class="active">{{ item.text }}</div>
    {% else  %}
	<div class="inactive">{{ item.text }}</div>
    {% end  %}
{% end %}

// Testing expression parser
{{ "f" * 8 + "u" * 8 + "~" }} should be ffffffffuuuuuuuu~
{{upper("f"*8+"u"*8+"~")}} should be FFFFFFFFUUUUUUUU~
{{ sin( 0 )}} should be 0
{{ cos( 0 ) }} should be 1
{{ length( [] ) }} should be 0
{{ length( [ 2, 4, { "s": 55 } ] ) }} should be 3
{{ length( { "key1": "value1", "key2": "value2" } ) }} should be 2
{{ 16 / 4 }} should be 4
{{ get( { "key1": "value1", "key2": "value2" }, "key2" ) }} should be value2
{{ get( numbers, "first" ) }} should be 5
{{ get( numbers, "second" ) }} should be 11
{{ get( numbers, "third" ) }} should be true
{{ get( numbers, "foo" ) }} should be null
{{ ( 2 + 2 ) * (2 + 2) }} should be 16

```
and the context which is represented above , we will get this output:
```

    
        <div class="inactive">Hello World!</div>
    

    
        <div class="active">Foo</div>
    

    
        <div class="inactive">Bar</div>
    


// Testing expression parser
ffffffffuuuuuuuu~ should be ffffffffuuuuuuuu~
FFFFFFFFUUUUUUUU~ should be FFFFFFFFUUUUUUUU~
0 should be 0
1 should be 1
0 should be 0
3 should be 3
2 should be 2
4 should be 4
value2 should be value2
5 should be 5
11 should be 11
true should be true
null should be null
16 should be 16

```

## Detailed description
### Functions
| Function name | Arguments  | Return value |
| :-----------: | :--------- | :----------- |
| sin           | `val` numeric | (numberic) sine of `val` radians |
| cos           | `val` numeric | (numberic) cosine of `val` radians |
| length        | `val` string or array or object | (numberic) length value of `val` Json object |
| not           | `val` bool | (bool) not `val` |
| get           | `val` string or array or object<br>`key` string or numeric | (any value or null) child item of `val` by `key` |
| lower         | `val` string | (string) lowered `val` |
| upper         | `val` string | (string) uppered `val` |

### Binary operators
| Operator | Left value | Right value | Return value |
| :------: | :--------- | :---------- | :----------- |
| +        | `lhs` numeric | `rhs` numeric | (numeric) addition of `lhs` and `rhs` |
| +        | `lhs` string | `rhs` string | (string) concatenated string of `lhs` and `rhs` |
| -        | `lhs` numeric | `rhs` numeric | (numeric) subtraction of `rhs` from `lhs` |
| *        | `lhs` numeric | `rhs` numeric | (numeric) multiplication of `lhs` and `rhs` |
| *        | `lhs` string | `rhs` numeric | (string) `lhs` string repeated `rhs` times |
| /        | `lhs` numeric | `rhs` numeric | (numeric) division of `lhs` by `rhs` |
| >        | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` > `rhs`. _Calls json11::Json approperiate operator_ |
| <        | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` < `rhs`. _Calls json11::Json approperiate operator_ |
| ==       | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` == `rhs`. _Calls json11::Json approperiate operator_ |
| !=       | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` != `rhs`. _Calls json11::Json approperiate operator_ |
| >=       | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` >= `rhs`. _Calls json11::Json approperiate operator_ |
| <=       | `lhs` any object | `rhs` any object | (bool) comparison of `lhs` <= `rhs`. _Calls json11::Json approperiate operator_ |
| &&       | `lhs` any object | `rhs` any object | (bool) logical AND of `lhs` and `rhs` |
| &#124;&#124; | `lhs` any object | `rhs` any object | (bool) logical OR of `lhs` and `rhs` |

All operators are being executed in this order:

1. *, /
2. +, -
3. >, <, ==, !=, <=, >=
4. &&, ||

# In Python
Having built RedZone python module, you can use the above classes in your own Python scripts, excepting there is no Json class -- Python dict replaces it completely.

```python
from RedZone import *

context = Context({                                               
"items": [                                   
      { "text": "Hello World!", "active": True },
      { "text": "Foo", "active": True },         
      { "text": "Bar", "active": False }         
],
"numbers": {
      "first": 5,
      "second": 11,
      "third": True
}
})
tpl = FileTemplate('test.tpl')

print tpl.render(context)
```
You get the same output.

# In plans
- extend template syntax with template inheritance
- ~~make Cython extension to use RedZone from Python~~
- add install/setup scripts
