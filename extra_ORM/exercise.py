import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "proj4_extra.settings")
import django
django.setup()
import query_funcs

def exercise():
    query_funcs.query1(1, 35, 40, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    query_funcs.query1(0, 0, 0, 0, 0, 0, 1, 6, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    query_funcs.query2('LightBlue')
    query_funcs.query2("Orange")
    query_funcs.query2("Green")
    query_funcs.query2("Red")
    query_funcs.query2("DarkBlue")
    query_funcs.query2("Gold")
    query_funcs.query2("Maroon")
    query_funcs.query2("Black")

    query_funcs.query3("BostonCollege");
    query_funcs.query3("Clemson");
    query_funcs.query3("Duke");

    query_funcs.query4("NC", "DarkBlue");
    query_funcs.query4("VA", "LightBlue");

    query_funcs.query5(5);
    query_funcs.query5(8);
