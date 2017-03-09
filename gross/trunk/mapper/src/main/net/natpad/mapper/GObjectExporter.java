package net.natpad.mapper;

import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;

import net.natpad.mapper.gobject.GObject;
import net.natpad.mapper.gobject.GObject.Name;

public class GObjectExporter {

	public final GObject object;
	
	public GObjectExporter(GObject object) {
		this.object = object;
	}
	

	
	public void export(File base) throws IOException {
		exportHeader(base);
		exportC(base);
	}

	
	@SuppressWarnings("resource")
	public void exportHeader(File base) throws IOException {
		File file = new File(base, object.name.as_PreName()+".h");
		PrintWriter outh = new PrintWriter(file);
		outh.println("/* generated */");
		
		Name n = object.name;
		
		
		outh.println("#ifndef "+n.as_PRE()+""+n.as_NAME()+"_H_");
		outh.println("#define "+n.as_PRE()+""+n.as_NAME()+"_H_");
		outh.println("");
		outh.println("#include <caterpillar.h>");
		outh.println("");
		outh.println("G_BEGIN_DECLS");
		outh.println("");
		outh.println("#define "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"              ("+n.as_pre_name()+"_get_type())");
		outh.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), "+n.as_pre_name()+"_get_type(), "+n.as_PreName()+"))");
		outh.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+", "+n.as_PreName()+"Class))");
		outh.println("#define "+n.as_PRE()+"_IS_"+n.as_NAME()+"(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"))");
		outh.println("#define "+n.as_PRE()+"_IS_"+n.as_NAME()+"_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"))");
		outh.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+", "+n.as_PreName()+"Class))");
		outh.println("");
		outh.println("typedef struct _"+n.as_PreName()+"               "+n.as_PreName()+";");
		outh.println("typedef struct _"+n.as_PreName()+"Private        "+n.as_PreName()+"Private;");
		outh.println("typedef struct _"+n.as_PreName()+"Class          "+n.as_PreName()+"Class;");
		outh.println("");
		outh.println("struct _"+n.as_PreName()+" {");
		outh.println("	GObject parent;");
		outh.println("};");
		outh.println("");
		outh.println("struct _"+n.as_PreName()+"Class {");
		outh.println("	GObjectClass parent_class;");
		outh.println("};");
		outh.println("");
		outh.println("GType "+n.as_pre_name()+"_get_type();");
		outh.println("");
		outh.println(""+n.as_PreName()+" *"+n.as_pre_name()+"_new(XanScanner *scanner);");
		outh.println("");
		outh.println("G_END_DECLS");
		outh.println("");
		outh.println("#endif /* "+n.as_PRE()+""+n.as_NAME()+"_H_ */");
		outh.flush();
		outh.close();
	}

	@SuppressWarnings("resource")
	public void exportC(File base) throws IOException {
		File file = new File(base, object.name.as_PreName()+".c");
		PrintWriter out = new PrintWriter(file);
		out.println("/* generated */");
		
		Name n = object.name;

		
		
		out.println("#include <logging/catlogdefs.h>
				out.println("#define CAT_LOG_LEVEL CAT_LOG_ALL
#define CAT_LOG_CLAZZ "XanParser"
#include <logging/catlog.h>

struct _XanParserPrivate {
	XanScanner *scanner;
};

static void l_stringable_iface_init(CatIStringableInterface *iface);

G_DEFINE_TYPE_WITH_CODE(XanParser, xan_parser, G_TYPE_OBJECT,
		G_ADD_PRIVATE(XanParser)
		G_IMPLEMENT_INTERFACE(CAT_TYPE_ISTRINGABLE, l_stringable_iface_init)
);

static void l_dispose(GObject *object);
static void l_finalize(GObject *object);

static void xan_parser_class_init(XanParserClass *clazz) {
	GObjectClass *object_class = G_OBJECT_CLASS(clazz);
	object_class->dispose = l_dispose;
	object_class->finalize = l_finalize;
}

static void xan_parser_init(XanParser *instance) {
}

static void l_dispose(GObject *object) {
	cat_log_detail("dispose:%p", object);
//			XanParser *instance = XAN_PARSER(object);
//			XanParserPrivate *priv = xan_parser_get_instance_private(instance);
	G_OBJECT_CLASS(xan_parser_parent_class)->dispose(object);
	cat_log_detail("disposed:%p", object);
}

static void l_finalize(GObject *object) {
	cat_log_detail("finalize:%p", object);
	cat_ref_denounce(object);
	G_OBJECT_CLASS(xan_parser_parent_class)->finalize(object);
	cat_log_detail("finalized:%p", object);
}


XanParser *xan_parser_new(XanScanner *scanner) {
	XanParser *result = g_object_new(XAN_TYPE_PARSER, NULL);
	cat_ref_anounce(result);
	XanParserPrivate *priv = xan_parser_get_instance_private(result);
	priv->scanner = cat_ref_ptr(scanner);
	return result;
}

		
		
		
		out.println("#ifndef "+n.as_PRE()+""+n.as_NAME()+"_H_");
		out.println("#define "+n.as_PRE()+""+n.as_NAME()+"_H_");
		out.println("");
		out.println("#include <caterpillar.h>");
		out.println("");
		out.println("G_BEGIN_DECLS");
		out.println("");
		out.println("#define "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"              ("+n.as_pre_name()+"_get_type())");
		out.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"(obj)              (G_TYPE_CHECK_INSTANCE_CAST ((obj), "+n.as_pre_name()+"_get_type(), "+n.as_PreName()+"))");
		out.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"_CLASS(klass)      (G_TYPE_CHECK_CLASS_CAST ((klass), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+", "+n.as_PreName()+"Class))");
		out.println("#define "+n.as_PRE()+"_IS_"+n.as_NAME()+"(obj)           (G_TYPE_CHECK_INSTANCE_TYPE ((obj), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"))");
		out.println("#define "+n.as_PRE()+"_IS_"+n.as_NAME()+"_CLASS(klass)   (G_TYPE_CHECK_CLASS_TYPE ((klass), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+"))");
		out.println("#define "+n.as_PRE()+"_"+n.as_NAME()+"_GET_CLASS(obj)    (G_TYPE_INSTANCE_GET_CLASS ((obj), "+n.as_PRE()+"_TYPE_"+n.as_NAME()+", "+n.as_PreName()+"Class))");
		out.println("");
		out.println("typedef struct _"+n.as_PreName()+"               "+n.as_PreName()+";");
		out.println("typedef struct _"+n.as_PreName()+"Private        "+n.as_PreName()+"Private;");
		out.println("typedef struct _"+n.as_PreName()+"Class          "+n.as_PreName()+"Class;");
		out.println("");
		out.println("struct _"+n.as_PreName()+" {");
		out.println("	GObject parent;");
		out.println("};");
		out.println("");
		out.println("struct _"+n.as_PreName()+"Class {");
		out.println("	GObjectClass parent_class;");
		out.println("};");
		out.println("");
		out.println("GType "+n.as_pre_name()+"_get_type();");
		out.println("");
		out.println(""+n.as_PreName()+" *"+n.as_pre_name()+"_new(XanScanner *scanner);");
		out.println("");
		out.println("G_END_DECLS");
		out.println("");
		out.println("#endif /* "+n.as_PRE()+""+n.as_NAME()+"_H_ */");
		out.flush();
		out.close();
	}

}
