package net.natpad.mapper.model;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class TypeList {

    public final TypeList parent;
    public final TypeDefinition typedef;
    
    public TypeList(TypeList parent, TypeDefinition typedef) {
        this.parent = parent;
        this.typedef = typedef;
    }
    
    public List<TypeDefinition> enlist() {
    	TypeList iter = this;
    	ArrayList<TypeDefinition> result = new ArrayList<TypeDefinition>();
    	while(iter!=null) {
    		result.add(typedef);
    		iter = iter.parent;
    	}
    	Collections.reverse(result);
    	return result;
    }
    
    
}
