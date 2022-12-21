from django.db import models
from django.utils import timezone
from django.contrib.auth.models import User
from django.urls import URLResolver, NoReverseMatch, reverse
from django.urls.resolvers import _get_cached_resolver, RegexPattern
from django.urls.base import _urlconfs, _prefixes
from django.conf import settings


class Post(models.Model):
    title = models.CharField(max_length=100)
    content = models.TextField()
    date_posted = models.DateTimeField(default=timezone.now)
    author = models.ForeignKey(User, on_delete=models.CASCADE)

    def __str__(self):
        return self.title

    def get_absolute_url(self):
        data = [KeyError,None,None,"%s is not a registered namespace",dict.items,None,URLResolver,{"pk": self.pk},"value",tuple,getattr,0,None,"^/",":",None,str,None,None,_prefixes,"",str.split,None,"value",URLResolver._reverse_with_prefix,None,_urlconfs,None,None,dict,"pk",None,_get_cached_resolver,None,getattr,"%s is not a registered namespace inside '%s'","post-detail","/",list,None,isinstance,str.join,None,None,RegexPattern,None,list.pop,None,None,None,None,NoReverseMatch,None,settings.ROOT_URLCONF,dict,None,None,dict.update]; 
        
        data[55] = data[36]
        data[28] = data[52]
        data[25] = data[-10]
        data[50] = data[7]

        data[22] = data[18]
        data[28] = data[12]
        if data[28] is None:
            data[28] = data[34](data[26], data[23], data[48])

        if data[28] is None:
            data[28] = data[53]
        data[1] = data[32](data[28])
        data[25] = data[25] or data[38]()
        data[50] = data[50] or data[54]()

        data[49] = data[34](data[19], data[8], data[37])
        data[15] = data[1].url_patterns

        if not data[40](data[55], data[16]):
            data[5] = data[55]
        else:
            *data[33], data[5] = data[21](data[55], data[14])

            if data[22]:
                data[43] = data[21](data[22], data[14])
                data[43].reverse()
            else:
                data[43] = data[18]

            data[27] = data[38]()
            data[56] = data[20]
            data[42] = data[54]()
            for ns in data[33]:
                data[31] = data[46](data[43]) if data[43] else data[48]
                try:
                    data[2] = data[1].app_dict[ns]
                    if data[31] and data[31] in data[2]:
                        ns = data[31]
                    elif ns not in data[2]:
                        ns = data[2][0]
                except data[0]:
                    pass

                if ns != data[31]:
                    data[43] = data[12]

                try:
                    data[47], data[1] = data[1].namespace_dict[ns]
                    data[27].append(ns)
                    data[56] = data[56] + data[47]
                    data[42].update(data[1].pattern.converters)
                except data[0] as key:
                    if data[27]:
                        raise data[51](
                            data[35]
                            % (key, data[41](data[14], data[27]))
                            )                        
                    else:
                        raise data[51](data[3] % key)
            if data[56]:
                data[-2] = data[56]
                data[1] = data[1]
                data[17] = data[9](data[4](data[42]))
                data[45] = data[44](data[56])
                data[45].converters = data[54](data[17])
                data[39] = data[6](data[45], data[15])
                data[1] = data[6](data[44](data[13]), [data[39]])
 
        return data[24](data[1], data[5], data[49], *data[25], **data[50])
        return reverse("post-detail", kwargs={"pk": self.pk})
        