package net.natpad.mapper.model;


public class TypeList {

    public final TypeList parent;
    public final TypeDefinition typedef;
    
    public TypeList(TypeList parent, TypeDefinition typedef) {
        this.parent = parent;
        this.typedef = typedef;
    }
    
}
