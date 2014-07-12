Base tempalte text!
{% block header %}
    {% if true %}
        Header text
    {% endif %}
{% endblock %}

{% block mainContent %}
This text should not be in output,
if this block is overloaded
{% endblock %}

{% block additionalContent %}
This text should be here if this block is not overloaded.
{% endblock %}

{% block footer %}
    Footer text
{% endblock %}
