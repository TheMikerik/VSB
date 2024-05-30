from django.contrib import admin
from .models import Cuser, Deck, Tag, Card, Review, Comment

# Register your models here.
admin.site.register(Cuser)
admin.site.register(Deck)
admin.site.register(Tag)
admin.site.register(Card)
admin.site.register(Review)
admin.site.register(Comment)