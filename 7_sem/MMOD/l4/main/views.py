from django.shortcuts import render

# Create your views here.
def index(request):
    template = 'index.html'
    context = {
        'stats_common': {
            'intensity': 0.4,
            'p0': 0.45,
            'pn': 0.54,
            'A': 0.18,
            'Q': 0.45,
            'p_rej': 0.54,
        },
        'stats_nominal': {
            'intensity': 0.4,
            'A': 0.18,
            'Q': 0.45,
        }
    }
    return render(request, template, context)