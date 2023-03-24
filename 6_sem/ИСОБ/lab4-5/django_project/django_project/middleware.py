import time
from django.conf import settings
from django.http import HttpResponseForbidden

class RequestLimitMiddleware:
    def __init__(self, get_response):
        self.get_response = get_response
        self.ip_count = {}
        self.ip_time = {}

    def __call__(self, request):
        ip = request.META.get('REMOTE_ADDR')
        current_time = time.time()

        # Check if the IP address requests density is more than allowed
        if ip in self.ip_count and self.ip_count[ip]/(current_time - self.ip_time[ip]) >= settings.MAX_REQUESTS_DENSITY:
            # Check if the IP address is currently in timeout
            if (current_time - self.ip_time[ip]) < settings.REQUESTS_DELAY:
                return HttpResponseForbidden('Too many requests. Please try again later.')
            else:
                # Reset the IP count and time
                self.ip_count[ip] = 0
                self.ip_time[ip] = current_time

        # Update the IP count and time
        if ip in self.ip_count:
            self.ip_count[ip] += 1
        else:
            self.ip_count[ip] = 1
            self.ip_time[ip] = current_time

        return self.get_response(request)