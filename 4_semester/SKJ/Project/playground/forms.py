from django import forms
from .models import Card, Cuser, Deck, Tag

class DeckForm(forms.ModelForm):
    class Meta:
        model = Deck
        fields = ['name', 'user']

class CardForm(forms.ModelForm):
    class Meta:
        model = Card
        fields = ['front_content', 'back_content', 'tags']

class CuserForm(forms.ModelForm):
    class Meta:
        model = Cuser
        fields = ['username', 'email', 'fname', 'lname']

class UserSelectForm(forms.Form):
    user = forms.ModelChoiceField(queryset=Cuser.objects.all(), label="Select User")

class TagForm(forms.ModelForm):
    class Meta:
        model = Tag
        fields = ['name']
        widgets = {
            'name': forms.TextInput(attrs={'class': 'form-control'}),
        }