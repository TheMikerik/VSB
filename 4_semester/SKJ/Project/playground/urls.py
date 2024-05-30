from django.urls import path
from . import views

#URLConf
urlpatterns = [
  path('', views.home, name='home'),

  path('decks/', views.deck_list, name='deck_list'),
  path('decks/<int:deck_id>/edit/', views.deck_edit, name='deck_edit'),
  path('decks/<int:deck_id>/delete/', views.deck_delete, name='deck_delete'),
  path('decks/add', views.deck_add, name='deck_add'),

  path('decks/<int:deck_id>/cards/', views.card_list, name='card_list'),
  path('cards/<int:card_id>/edit/', views.card_edit, name='card_edit'),
  path('cards/<int:card_id>/delete/', views.card_delete, name='card_delete'),
  path('decks/<int:deck_id>/cards/add/', views.card_add, name='card_add'),

  path('decks/<int:deck_id>/comments/', views.comment_list, name='comment_list'),
  path('decks/<int:deck_id>/comments/add/', views.add_comment, name='add_comment'),

  path('users/', views.user_list, name='user_list'),
  path('users/<int:user_id>/edit/', views.user_edit, name='user_edit'),
  path('users/<int:user_id>/delete/', views.user_delete, name='user_delete'),
  path('user/add/', views.user_add, name='user_add'),

  path('decks/<int:deck_id>/practice/', views.practice, name='practice'),
  path('deck/<int:deck_id>/user_select/', views.user_select, name='user_select'),

  path('reviews/', views.review_list, name='review_list'),

  path('add_tag/', views.add_tag, name='add_tag'),
]