from django.urls import path
from . import views

#URLConf
urlpatterns = [
  path('', views.home, name='home'),
  path('decks/', views.deck_list, name='deck_list'),
  path('decks/<int:deck_id>/edit/', views.deck_edit, name='deck_edit'),
  path('decks/<int:deck_id>/delete/', views.deck_delete, name='deck_delete'),
  path('decks/add', views.deck_add, name='deck_add'),
]