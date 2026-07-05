# Bit Fields

Bit fields are a feature that allows for the compact storage of data
within structures by specifying the exact number of bits a member should occupy.

> [!CAUTION]
> The C standard leaves many aspects of bit field implementation undefined, such
as the order of allocation within a storage unit (left-to-right or right-to-left),
whether they can cross storage unit boundaries, and the size and alignment of the
underlying storage unit. This means code relying on specific bit field layouts
may behave differently across compilers and architectures.

**[Use example](app/Src/main.c)**