package net.natpad.mapper.model;


public class TypeDefinition {

    public final String typename;
    public final Block block;
    
    public TypeDefinition(String typename, Block block) {
        this.typename = typename;
        this.block = block;
    }

}
