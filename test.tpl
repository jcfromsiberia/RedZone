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
{{ 2 + " + 2 = 4" }} should be 2 + 2 = 4
