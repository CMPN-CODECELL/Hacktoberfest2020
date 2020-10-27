from django.urls import path
from .import views
from .views import (BookListView,BookDetailView,AuthorListView,AuthorDetailView,LoanedBooksByUserListView,
	LoanedBooksAllListView,AuthorCreate,AuthorUpdate,AuthorDelete,BookCreate,BookUpdate,BookDelete,
	GenreCreate,GenreUpdate,GenreDelete,BookInstanceCreate,BookInstanceUpdate,BookInstanceDelete,
	GenreListView,RegistrationForm)

app_name = 'catalog'

urlpatterns = [
	path('', views.index, name='index'),
	path('books/', BookListView.as_view(), name='books'),
	path('book/<int:pk>',BookDetailView.as_view(), name='book-detail'),
	path('authors/', AuthorListView.as_view(), name='authors'),
	path('author/<int:pk>',AuthorDetailView.as_view(), name='author-detail'),
	path('genres/', GenreListView.as_view(), name='genres'),
	path('genre/<str:name>', views.detail, name='genre-detail'),
	path('mybooks/', LoanedBooksByUserListView.as_view(), name='my-borrowed'),
	path(r'borrowed/', LoanedBooksAllListView.as_view(), name='all-borrowed'),
	path('book/<uuid:pk>/renew/', views.renew_book_librarian, name='renew-book-librarian'),
	path('author/create/', AuthorCreate.as_view(), name='author_create'),
        path('author/<int:pk>/update/', AuthorUpdate.as_view(), name='author_update'),
        path('author/<int:pk>/delete/', AuthorDelete.as_view(), name='author_delete'),
        path('book/create/', BookCreate.as_view(), name='book_create'),
        path('book/<int:pk>/update/', BookUpdate.as_view(), name='book_update'),
        path('book/<int:pk>/delete/', BookDelete.as_view(), name='book_delete'),
        path('genre/create/', GenreCreate.as_view(), name='genre_create'),
        path('genre/<int:pk>/update/',GenreUpdate.as_view(), name='genre_update'),
        path('genre/<int:pk>/delete/', GenreDelete.as_view(), name='genre_delete'),
        path('book_instance/create/', BookInstanceCreate.as_view(), name='book_instance_create'),
        path('book_instance/<uuid:pk>/update/',BookInstanceUpdate.as_view(), name='book_instance_update'),
        path('book_instance/<uuid:pk>/delete/', BookInstanceDelete.as_view(), name='book_instance_delete'),
        path('signup/', views.register, name='signup'),
]
