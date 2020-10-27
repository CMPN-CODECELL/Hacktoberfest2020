import datetime
from django import forms
from django.core.exceptions import ValidationError
from django.utils.translation import ugettext_lazy as _
from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm

class RenewBookForm(forms.Form):
    renewal_date = forms.DateField(help_text="Enter a date between now and 4 weeks (default 3).")
    print("renew",renewal_date)

    #defining validations
    def clean_renewal_date(self): #easiest way to validate a field is to override method by this func for the field u want to check
        data = self.cleaned_data['renewal_date']  #date which is extracted after submitting form textarea
        print("data22",data)
        
        # Check if a date is not in the past. 
        if data < datetime.date.today():
            raise ValidationError(_('Invalid date - renewal in past'))

        # Check if a date is in the allowed range (+4 weeks from today).
        if data > datetime.date.today() + datetime.timedelta(weeks=4):
            raise ValidationError(_('Invalid date - renewal more than 4 weeks ahead'))

        # Remember to always return the cleaned data.
        return data

class RegistrationForm(UserCreationForm):
 
    class Meta:
        model = User
        fields = ['username','first_name','last_name','email','password1','password2']

        def clean_form(self):
            first_name = self.cleaned_data['first_name']
            last_name = self.cleaned_data['last_name']
            email = self.cleaned_data['email']

            return first_name,last_name,email



