col. 1    : blank, or a "c" or "*" for comments
col. 1-5  : statement label (optional)
col. 6    : continuation of previous line (optional, any character)
col. 7-72 : statements, ! is comment use inside statement
col. 73-80: sequence number (optional, rarely used today)

      program test
c implicit rule for type assign to undeclare variable , default implicit rule i-n is integer type
      implicit none ! disable implicit declare variable
c     implicit double precision (a-h,o-z)! a-h and o-z character start letter follow this implicit rule

      real x, y ! power notation follow by E
      logical d
      integer i
      double precision w ! power notation follow by D
      character str*20
      complex(16) z
      parameter (y = 1E1, w=1D1) ! define y as a constant 10, which cannot be modify (compile error)
c     y = 11 ! this will cause compile error


c simple IO read/write(fileno, format) list-of-variables
      write (*, *) 'input x:'
      read (*, *) x
      write (*, *) 'x=', x 

c format IO

c complex number assignment
      z = (1.2, 3.4) ! (real, imag)
      write (*, *) 'z=', z 

c logical number assignment
      d = .false. ! logical value need use . to enclose 
      write (*, *) 'd=', d

      str='fortran ''test''' ! use '' to print '
      write (*, *) 'str=', str

c type conversion --> int, real, dble, ichar, char
      i = ichar(str(1:1)) ! character need to use sub-string notation to extract value
      write (*, *) i
      
      stop ! exit program, use to emphasize
      end 
