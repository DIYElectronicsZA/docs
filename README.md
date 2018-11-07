<h2>DIYElectronics Wiki Documentation</h2>

<h3>
Created with mkdocs.
Written in markdown.
Compiled to HTML.
</h3>
<b>Instructions for setting up wiki on different pc:</b>  


1)You will have to install and set up mkdocs.  
2) The current wiki uses modified themes for mkdocs, so you may want to copy the themes from this wiki to replace.   
    Otherwise the colour and format will not be the same. (Mkdocs themes stored in site-packages in python folder)  
3) Clone the repository for the wiki https://github.com/DIYElectronicsZA/docs  
4)To edit pages of the wiki, work in the docs folder.  
5)Docs are sorted according to category.  
6)Documents are written in Markdown format (.md extension) and images are stored in corresponding /img folders.  
7) When adding a new page to the wiki you will have to edit the mkdocs.yml file  
    (this file is responsible for generating the menu bar and building the files).  
     Add the page to the relevant category.  
8)the index.md file found in the docs folder is the homepage of the wiki.  
9)Once changes have been made you will have to compile the docs.  

<b>To compile wiki.</b>   

1)Open a command prompt and change directories to the folder where wiki is stored (same directory as the mkdocs.yml page)  
2)To view changes locally first, type "mkdocs serve" in the command prompt and navigate to the IP address displayed.  
3) To compile the wiki type "mkdocs build", if there are any critical errors with the wiki,  
    they will be displayed now in the command prompt.   
4)If there are no errors and the wiki has succeffully compiled you can copy the contents of the "site" folder to the server,   
    replacing all the files.   
