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

## How to use?

Link RedZone library to your application or library and use these following classes inside:

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
         ]                                            
      }                                               
       )", err ) );
```

#### RedZone::Context
Rendering context accepts json object-type instances only. You can not pass arrays or something else.
`RedZone::Template` classes have `render` method to render the template with user context into a `stream`.
``` cpp
RedZone::Context context( json ); 
tpl.render( std::cout, &context);
```

So, if we have this markup in `/tmp/test.tpl`:
```
{% each items as item %}
    {% if item.active == true %}
    <div>{{item.text}}</div>
    {% else %}
    <span>Skipped</span>
    {% end %}
    Some text.
{% end %}
```
We will get this output:
```

    
    <div>Hello World!</div>
    
    Some text.

    
    <div>Foo</div>
    
    Some text.

    
    <span>Skipped</span>
    
    Some text.

```
