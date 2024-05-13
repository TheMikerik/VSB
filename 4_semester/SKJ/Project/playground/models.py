from django.db import models

class Cuser(models.Model):
    username = models.CharField(max_length=50)
    email = models.EmailField(max_length=100)
    fname = models.CharField(max_length=50)
    lname = models.CharField(max_length=50)

class Deck(models.Model):
    name = models.CharField(max_length=100)
    user = models.ForeignKey(Cuser, on_delete=models.CASCADE)

class Tag(models.Model):
    name = models.CharField(max_length=50)

class Card(models.Model):
    front_content = models.TextField()
    back_content = models.TextField()
    deck = models.ForeignKey(Deck, on_delete=models.CASCADE)
    tags = models.ManyToManyField(Tag)

class Review(models.Model):
    user = models.ForeignKey(Cuser, on_delete=models.CASCADE)
    card = models.ForeignKey(Card, on_delete=models.CASCADE)
    date_reviewed = models.DateTimeField(auto_now_add=True)

class Comment(models.Model):
    user = models.ForeignKey(Cuser, on_delete=models.CASCADE)
    card = models.ForeignKey(Card, on_delete=models.CASCADE)
    text = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)
