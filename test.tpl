{# Testing inheritance #}

Before extends
{% extends middle_test.tpl %}
{% block mainContent %}
{# Testing loop and condition tags #}
{% for item in items %}
    {% if item.active && length(item.text) == 3 %}
    <div class="active">{{ item.text }}</div>
    {% else  %}
    <div class="inactive">{{ item.text }}</div>
    {% endif %}
{% endfor %}

{# Testing expression parser #}
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
{{ contains( "item1", { "item2": [ 2 ], "item1": "str" } ) }} should be true
{{ contains( 2, [ 1, 1, 1, 2, 3, 3 ] ) }} should be true
{{ contains( "ada", "abracadabra" ) }} should be true
{{ to_json( { "key1": "value1", "key2": [ 2, 4, 6] } ) }} should be { "key1": "value1", "key2": [ 2, 4, 6] }

{# Testing include tag #}
{% if true %}
    {% include [ "inc_test.tpl" ] %}
{% else %}
    {% include "Fake.tpl" %} 
{% endif %}

Numbers:
{% for key,value in numbers %}
   Key: {{ key }}, value: {{ value }}
{% endfor %}

{# Testing cache #}

{% cache 5000 "TestCache" %}{{ random(20, 100500) }}{% endcache %} should be {% cache 5000 "TestCache" %}{{ random(20, 100500) }}{% endcache %} cached

{% endblock %}

This text should not be here!
{% endextends %}
