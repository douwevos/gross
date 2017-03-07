package net.natpad.mapper.model;


public class FieldList {

    public final FieldList parent;
    public final Field field;
    
    public FieldList(FieldList parent, Field field) {
        this.parent = parent;
        this.field = field;
    }

}
