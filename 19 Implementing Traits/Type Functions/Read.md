**Type Functions:** functions that taskes some type as atguments and produce a type or aconstant as a result.
* sizeof: a very useful build-in type functions;
* ElementT: the type ElementT is called a *traits class*;
* Transformation Traits: In addition to providing access to particular aspects of a main parameter type, traits can also perform transformations on types, such as adding or removing references or const and volatile qualifiers.
    * Remove References
    * Adding References
    * Removing Qualifiers
    * Decay
* Predicate Traits
    * IsSame
    * True_type and False_type
* Result Type Traits: is very useful when writing operator templates.

###Example(Element Types):

How is a type function useful? It allows us to parameterize a template in terms of a container type without also requiring parameters for the element type and other characteristics. 

For example, instead of:
```cpp
//old version
template<typename T, typename C>
T sumOfElements(C const& c);

//new version
template<typename C>
typename ElementT<C>::Type sumOfElement(C const& c);
```