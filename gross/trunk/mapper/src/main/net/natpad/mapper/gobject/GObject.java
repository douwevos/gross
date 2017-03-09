package net.natpad.mapper.gobject;

public class GObject {

	
	private Name parentObjectName = new Name("G", "Object"); 
	public final Name name;
	
	public GObject(Name name) {
		this.name = name;
	}
	
	
	public static class Name {
		public final String prefix;
		public final String name;

		public Name(String prefix, String name) {
			this.prefix = prefix;
			this.name = name;
		}
		
		public String as_PreName() {
			return prefix+name;
		}
		
		public String as_pre_name() {
			return prefix.toLowerCase()+"_"+name.toLowerCase();
		}
		
		public String as_PRE() {
			return prefix.toUpperCase();
		}
		
		public String as_NAME() {
			return name.toUpperCase();
		}
		
	}
}
