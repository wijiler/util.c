# W(ij) D(ocumentation) S(tandard)

## [The best way to use comments;an explanation of my comments]


comments are a simple thing,but if not used correctly they're useless  
Heres what comments should be at best  
- descriptive
- easy to read
- fast to type 
  
So enough of the fluff lets get into the standard:  
```
Descrip function |> {
    Declares that this is a general description of whatever you're documenting,
    USES |> {
    Descrip [DESCRIPTION OPTIONS],
    Descrip => DESCRIPTION,
    }
}
Param function |> {
    Declares a description and use of a parameter,
    USE =>
        Param(PARAMNAME) | TYPE => PARAMATER DESCRIPTION
}
Return function |> {
    Declares what return statement means,
    USE =>
        Return => [VALUE1;VALUE2;VALUE3]
}
Syntax |> {
    Arrays,options,and optionals |> {
        Arrays are declared as such
        ARRNAME |> {E1,E2}
        Options are like arrays but only one value is true and are declared as such
        [OPT1;OPT2]
        They way you declare an [optional;boolean] is (NAME)
    },
    Operators |> {
        |> |> { The |> operator is [ (describe each thing in an optional);Declare array]  },
        | |> { A way to provide types of arguments of a function },
        => |> { [this equals to;this is the text that describes this function] |> less common,less complicated |> most common,more complicated }
    } 
}
```
heres what I believe this syntax acheives
- [x] descriptive
- [] easy to read (only if you havent read this doc)
- [x] fast to type

and heres a real world example of this in this project from `alloc/arena.h`
```c++
/*
 * Descrip => allocates a new pool of memory to an arena allocater
 * Param(a) | arena* => the arena you want to alloc to
 * Param(data) | void* => the variable you want to allocate in the new pool
 */
void arena_alloc_var(arena* a, void* data)
{
  if (a->start->next == NULL)
    {
      a->end = nreg(data);
      a->start->next = a->end;
      return;
    }
  else if(a->start->next == a->end)
    {
      struct pool* npool = nreg(data);
      struct pool* oend = nreg(a->end->data);
      a->start->next = oend; a->end = npool; a->start->next->next = a->end;
      return;
    }
    struct pool* lp = a->start->next;
    while (lp != a->end)
      lp = lp->next;
    struct pool* oend = nreg_ll(a->end->data);
    lp->next = oend;
    a->end = nreg(data);
}
```
