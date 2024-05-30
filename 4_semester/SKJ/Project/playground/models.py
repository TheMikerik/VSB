from django.db import models

class Cuser(models.Model):
    username = models.CharField(max_length=50)
    email = models.EmailField(max_length=100)
    fname = models.CharField(max_length=50)
    lname = models.CharField(max_length=50)
    def __str__(self):
        return self.username

class Deck(models.Model):
    name = models.CharField(max_length=100)
    user = models.ForeignKey(Cuser, on_delete=models.CASCADE)
    def __str__(self):
        return self.name

class Tag(models.Model):
    name = models.CharField(max_length=50)
    def __str__(self):
        return self.name

class Card(models.Model):
    front_content = models.TextField()
    back_content = models.TextField()
    deck = models.ForeignKey(Deck, on_delete=models.CASCADE)
    tags = models.ManyToManyField(Tag)
    def __str__(self):
        return f"{self.front_content[:30]}..."

class Review(models.Model):
    user = models.ForeignKey(Cuser, on_delete=models.CASCADE)
    deck = models.ForeignKey(Deck, on_delete=models.CASCADE)
    date_reviewed = models.DateTimeField(auto_now_add=True)

class Comment(models.Model):
    deck = models.ForeignKey(Deck, on_delete=models.CASCADE)
    nicname = models.CharField(max_length=50)
    text = models.TextField()
    created_at = models.DateTimeField(auto_now_add=True)
