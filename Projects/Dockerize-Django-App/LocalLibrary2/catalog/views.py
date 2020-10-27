from django.shortcuts import render
from catalog.models import Book, Author, BookInstance, Genre, Language 
from django.shortcuts import get_object_or_404
from django.views.generic import (ListView,DetailView)
from django.contrib.auth.mixins import LoginRequiredMixin
from django.contrib.auth.mixins import PermissionRequiredMixin
import datetime
from django.contrib.auth.decorators import permission_required
from django.http import HttpResponseRedirect
from django.urls import reverse
from catalog.forms import RenewBookForm,RegistrationForm
from django.views.generic.edit import CreateView, UpdateView, DeleteView
from django.urls import reverse_lazy
from django.contrib.auth.forms import UserCreationForm
from django.urls import reverse_lazy
from django.contrib.auth.models import User

def index(request):
    num_books = Book.objects.all().count()
    num_instances = BookInstance.objects.all().count()
    num_instances_available = BookInstance.objects.filter(status__exact='a').count()    
    num_authors = Author.objects.count()

    context = {
        'num_books': num_books,
        'num_instances': num_instances,
        'num_instances_available': num_instances_available,
        'num_authors': num_authors,
    }

    return render(request, 'catalog/index.html', context=context)


class BookListView(ListView):
    model = Book
    paginate_by = 6

    def get_queryset(self):
        return Book.objects.all().order_by('title')
   


class BookDetailView(DetailView):
    model = Book


class AuthorListView(ListView):
	model = Author
	paginate_by = 6
	
	def get_queryset(self):
		return Author.objects.all().order_by('last_name')


class AuthorDetailView(DetailView):
	model = Author


class GenreListView(ListView):
    model = Genre
    paginate_by = 6

    def get_queryset(self):
        return Genre.objects.all().order_by('name')
    

def detail(request,name):
    Books = Book.objects.filter(genre__name=name)
    context = {'Books':Books,'name':name}
    return render(request , 'catalog/bookgenre.html',context)


class LoanedBooksByUserListView(LoginRequiredMixin,ListView):
    """Generic class-based view listing books on loan to current user."""
    model = BookInstance
    template_name ='catalog/bookinstance_list_borrowed_user.html'
    paginate_by = 6
    
    def get_queryset(self):
        return BookInstance.objects.filter(borrower=self.request.user).filter(status__exact='o').order_by('due_back')


class LoanedBooksAllListView(PermissionRequiredMixin,ListView):
    model = BookInstance
    permission_required = 'catalog.can_mark_returned'
    template_name = 'catalog/bookinstance_list_borrowed_all.html'
    paginate_by = 6

    def get_queryset(self):
        return BookInstance.objects.filter(status__exact='o').order_by('due_back')


@permission_required('catalog.can_mark_returned')
def renew_book_librarian(request, pk):
    """View function for renewing a specific BookInstance by librarian."""
    book_instance = get_object_or_404(BookInstance, pk=pk)
    print("bukin",book_instance)

    # If this is a POST request then process the Form data
    if request.method == 'POST':

        # Create a form instance and populate it with data from the request (binding):
        form = RenewBookForm(request.POST)
        print("formsss",form)

        # Check if the form is valid:
        if form.is_valid():
            # process the data in form.cleaned_data as required (here we just write it to the model due_back field)
            book_instance.due_back = form.cleaned_data['renewal_date']
            print("a",form.cleaned_data['renewal_date'])  #saved date
            book_instance.save()


    # If this is a GET (or any other method) create the default form.
    else:
        proposed_renewal_date = datetime.date.today() + datetime.timedelta(weeks=3)
        print("proposed",proposed_renewal_date)
        form = RenewBookForm(initial={'renewal_date': proposed_renewal_date})

    context = {
        'form': form,
        'book_instance': book_instance,
    }

    return render(request, 'catalog/book_renew_librarian.html', context)


class AuthorCreate(PermissionRequiredMixin,CreateView):
    model = Author
    fields = '__all__'
    permission_required = 'catalog.can_mark_returned'
    initial = {'date_of_death': '05/01/2018'}
    success_url = '/catalog/authors/'

class AuthorUpdate(PermissionRequiredMixin,UpdateView):
    model = Author
    fields = ['first_name', 'last_name', 'date_of_birth', 'date_of_death']
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/authors/'

class AuthorDelete(PermissionRequiredMixin,DeleteView):
    model = Author
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/authors/'

class BookCreate(PermissionRequiredMixin,CreateView):
    model = Book
    fields = '__all__'
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/books/'

class BookUpdate(PermissionRequiredMixin,UpdateView):
    model = Book
    fields = '__all__'
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/books/'

class BookDelete(PermissionRequiredMixin,DeleteView):
    model = Book
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/books/'

class GenreCreate(PermissionRequiredMixin,CreateView):
    model = Genre
    permission_required = 'catalog.can_mark_returned'
    fields = '__all__'
    success_url = '/catalog/genres/'

class GenreUpdate(PermissionRequiredMixin,UpdateView):
    model = Genre
    permission_required = 'catalog.can_mark_returned'
    fields = '__all__'
    success_url = '/catalog/genres/'

class GenreDelete(PermissionRequiredMixin,DeleteView):
    model = Genre
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/genre/'

class BookInstanceCreate(PermissionRequiredMixin,CreateView):
    model = BookInstance
    permission_required = 'catalog.can_mark_returned'
    fields = '__all__'
    success_url = '/catalog/borrowed/'

class BookInstanceUpdate(PermissionRequiredMixin,UpdateView):
    model = BookInstance
    permission_required = 'catalog.can_mark_returned'
    fields = '__all__'
    success_url = '/catalog/borrowed/'

class BookInstanceDelete(PermissionRequiredMixin,DeleteView):
    model = BookInstance
    permission_required = 'catalog.can_mark_returned'
    success_url = '/catalog/borrowed/'


from django.contrib.auth.models import User
from django.contrib.auth.forms import UserCreationForm

def register(request):
    if request.method =='POST':
        form = RegistrationForm(request.POST)
        if form.is_valid():
            form.save()
            return HttpResponseRedirect(reverse('catalog:my-borrowed') )

    else:
        form = RegistrationForm()

    arg = {'form':form}
    return render(request,'catalog/signup.html',arg)




