# Generated by Django 5.0.6 on 2024-05-14 07:09

import django.db.models.deletion
from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('playground', '0003_remove_cuser_password_cuser_fname_cuser_lname'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='comment',
            name='card',
        ),
        migrations.RemoveField(
            model_name='review',
            name='card',
        ),
        migrations.AddField(
            model_name='comment',
            name='Deck',
            field=models.ForeignKey(default=0, on_delete=django.db.models.deletion.CASCADE, to='playground.deck'),
            preserve_default=False,
        ),
        migrations.AddField(
            model_name='review',
            name='Deck',
            field=models.ForeignKey(default=0, on_delete=django.db.models.deletion.CASCADE, to='playground.deck'),
            preserve_default=False,
        ),
    ]
