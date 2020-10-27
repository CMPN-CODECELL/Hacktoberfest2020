from django.contrib import admin
from catalog.models import Author, Genre, Book, BookInstance, Language


@admin.register(Author) #can use instead of admin.site.register()
class AuthorAdmin(admin.ModelAdmin):
    list_display = ('last_name', 'first_name', 'date_of_birth', 'date_of_death')  #___str__ can show not enough info so it is used to show more info
    fields = ['first_name', 'last_name', ('date_of_birth', 'date_of_death')] #to change order of field


class BooksInstanceInline(admin.TabularInline):
    model = BookInstance

    
@admin.register(Book)
class BookAdmin(admin.ModelAdmin):
    list_display = ('title', 'author')
    inlines = [BooksInstanceInline]


@admin.register(BookInstance) 
class BookInstanceAdmin(admin.ModelAdmin):
    list_display = ('id','book','status','borrower','due_back')
    list_filter = ('status','due_back')
    #sectioning the detail view
    fieldsets = (          
        (None, {
            'fields': ('book', 'imprint', 'id')
        }),
        ('Availability', {
            'fields': ('status', 'due_back','borrower')
            #'fields': [('status', 'due_back')]  to change order
        }),
    )


admin.site.register(Genre)
admin.site.register(Language)

