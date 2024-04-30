OPTIONS = -framework GLUT -framework OpenGL
DEFINES = -D GL_SILENCE_DEPRECATION

OBJDIR = ../mylib
OBJS = $(OBJDIR)/initShader.o $(OBJDIR)/vec.o
project4: project4.c $(OBJS)
	gcc -o project4 project4.c $(OBJS) $(OPTIONS) $(DEFINES)

$(OBJDIR)/%.o: %.c %.h
		$(CC) -c @< -o $@ $(CFLAGS)
