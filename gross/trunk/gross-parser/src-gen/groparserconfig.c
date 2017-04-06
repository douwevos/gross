#include "groparserconfig.h"

const int gro_parser_config_nr_of_symbols = 48;
static const GroRunSymbolDescription symbols[] = {
		  { FALSE, "⟧", 0} 
		, { FALSE, "⊗", 1} 
		, { TRUE, "◎", 2} 
		, { FALSE, "SEMI", 3} 
		, { FALSE, "RULE_SEPERATOR", 4} 
		, { FALSE, "IDENTIFIER", 5} 
		, { FALSE, "COLON", 6} 
		, { FALSE, "COMMA", 7} 
		, { FALSE, "TERMINAL", 8} 
		, { FALSE, "STAR", 9} 
		, { FALSE, "PLUS", 10} 
		, { FALSE, "EXCL", 11} 
		, { FALSE, "BAR", 12} 
		, { FALSE, "INDEX_MARK", 13} 
		, { FALSE, "CODE", 14} 
		, { FALSE, "CODE_TEXT", 15} 
		, { FALSE, "NUMBER", 16} 
		, { FALSE, "IMPORTS", 17} 
		, { FALSE, "TYPE", 18} 
		, { FALSE, "LPAREN", 19} 
		, { FALSE, "RPAREN", 20} 
		, { FALSE, "LSQBRACK", 21} 
		, { FALSE, "RSQBRACK", 22} 
		, { FALSE, "LCUBRACK", 23} 
		, { FALSE, "RCUBRACK", 24} 
		, { TRUE, "spec", 25} 
		, { TRUE, "term_decl_list", 26} 
		, { TRUE, "term_decl", 27} 
		, { TRUE, "ids", 28} 
		, { TRUE, "name", 29} 
		, { TRUE, "production_list", 30} 
		, { TRUE, "production", 31} 
		, { TRUE, "rhs_rule_list", 32} 
		, { TRUE, "rhs_rule", 33} 
		, { TRUE, "rhs_rule_part_list", 34} 
		, { TRUE, "rhs_rule_part", 35} 
		, { TRUE, "rhs_entry_complete", 36} 
		, { TRUE, "rhs_entry", 37} 
		, { TRUE, "opt_label", 38} 
		, { TRUE, "rhs_sub_list", 39} 
		, { TRUE, "rhs_sub", 40} 
		, { TRUE, "imports_code", 41} 
		, { TRUE, "type_definition_list", 42} 
		, { TRUE, "type_definition", 43} 
		, { TRUE, "code_definition_list", 44} 
		, { TRUE, "code_definition", 45} 
		, { TRUE, "prod_rule_ref", 46} 
		, { TRUE, "code_text", 47} 
};
const GroRunSymbolDescription *gro_parser_config_symbols = symbols;

const int gro_parser_config_nr_of_states = 77;
const char *gro_parser_config_states_text =
				  "r25,2,0p2r26,2,0p3r30,1p11r29,1p9r28,1p8r30,2p10r25,5,0,3,4p1r25,2p2r26,2p3r33,2,1p15r32,1p14r27,3p6"
				  "r27,3p5r25,5,0,4p1r25,5,0,3p1r42,2,0p34r44,2,0p37r41,2p33r47,1p43r25,5,3,4p1r32,2p13r31,3p12r34,2,0p"
				  "17r35,1p19r37,2,1p26r33,2p15r36,1p20r28,3p7r25,5,0p1r42,2p34r44,2p37r46,1p40r25,5,4p1r25,5,3p1r39,1p"
				  "30r40,1p32r37,2p26r34,2p17r36,2p21r36,2p22r36,2p23r33,4,3p16r45,3p39r25,5p1r40,2p31r37,3p24r37,3p25r"
				  "38,2p27r33,4p16r46,3p41r46,3p42r43,4p36r39,3p29A0B26S6B29S7B5S8B27S3B30S2B25S4B31S5B8S1A1B29S9B28S11"
				  "B1S10B5S8A2B29S7B0R0,-1B17S14B5S8B31S12B41S13A3B29R1,-1B5R1,-1B30R1,-1B31R1,-1B8R1,-1A4B0EA5B0R2,-1B"
				  "29R2,-1B17R2,-1B5R2,-1A6B29S7B5S8B27S16B30S15B31S5B8S1A7B13S20B33S19B32S17B4S18A8B19R3,-1B15R3,-1B6R"
				  "3,-1B9R3,-1B29R3,-1B22R3,-1B13R3,-1B37R3,-1B10R3,-1B3R3,-1B20R3,-1B32R3,-1B5R3,-1B11R3,-1B7R3,-1B12R"
				  "3,-1B21R3,-1B28R3,-1B33R3,-1B4R3,-1B36R3,-1A9B3R4,-1B7R4,-1A10B3S21A11B3S23B7S22A12B0R5,-1B29R5,-1B1"
				  "7R5,-1B5R5,-1A13B0R6,-1B42S24B14S26B43S27B18S28B44S25B45S29A14B47S30B15S31A15B29S7B0R7,-1B17S14B5S8B"
				  "31S12B41S32A16B29R8,-1B5R8,-1B30R8,-1B31R8,-1B8R8,-1A17B13S20B3S34B33S33B4S18A18B19S37B35S35B29S39B3"
				  "7S41B13R9,-1B34S40B3R9,-1B21S38B5S8B4R9,-1B36S36A19B13R10,-1B3R10,-1B4R10,-1A20B29S42B5S8A21B29R11,-"
				  "1B5R11,-1B30R11,-1B31R11,-1B8R11,-1A22B29S43B5S8A23B29R12,-1B5R12,-1B30R12,-1B31R12,-1B8R12,-1A24B0R"
				  "13,-1B14S26B43S45B18S28B44S44B45S29A25B0R14,-1B14S26B45S46A26B29S48B5S8B46S47A27B0R15,-1B14R15,-1B18"
				  "R15,-1B44R15,-1B45R15,-1A28B29S49B5S8A29B0R16,-1B14R16,-1A30B0R17,-1B42R17,-1B14R17,-1B43R17,-1B18R1"
				  "7,-1B44R17,-1B45R17,-1A31B0R18,-1B42R18,-1B14R18,-1B43R18,-1B18R18,-1B44R18,-1B45R18,-1A32B0R19,-1B4"
				  "2S50B14S26B43S27B18S28B44S51B45S29A33B13R20,-1B3R20,-1B4R20,-1A34B0R21,-1B29R21,-1B17R21,-1B5R21,-1A"
				  "35B19R22,-1B29R22,-1B37R22,-1B13R22,-1B3R22,-1B21R22,-1B5R22,-1B4R22,-1B36R22,-1A36B19R23,-1B29R23,-"
				  "1B37R23,-1B13R23,-1B3R23,-1B21R23,-1B5R23,-1B4R23,-1B36R23,-1A37B19S37B29S39B39S54B37S41B21S38B5S8B3"
				  "6S53B40S52A38B19S37B29S39B39S55B37S41B21S38B5S8B36S53B40S52A39B19R24,-1B6S57B9R24,-1B29R24,-1B22R24,"
				  "-1B37R24,-1B13R24,-1B10R24,-1B3R24,-1B20R24,-1B5R24,-1B11R24,-1B12R24,-1B21R24,-1B4R24,-1B36R24,-1B3"
				  "8S56A40B19S37B35S58B29S39B37S41B13R25,-1B3R25,-1B21S38B5S8B4R25,-1B36S36A41B19R26,-1B9S59B29R26,-1B2"
				  "2R26,-1B37R26,-1B13R26,-1B10S60B3R26,-1B20R26,-1B5R26,-1B11S61B12R26,-1B21R26,-1B4R26,-1B36R26,-1A42"
				  "B4S62A43B3R27,-1B7R27,-1A44B0R28,-1B14S26B45S46A45B0R29,-1B14R29,-1B18R29,-1B44R29,-1B45R29,-1A46B0R"
				  "30,-1B14R30,-1A47B47S63B15S31A48B15R31,-1B13S64A49B29S9B28S65B5S8A50B0R32,-1B14S26B43S45B18S28B44S66"
				  "B45S29A51B0R33,-1B14S26B45S46A52B19S37B29S39B22R34,-1B37S41B12R34,-1B21S38B20R34,-1B5S8B36S67A53B19R"
				  "35,-1B29R35,-1B22R35,-1B37R35,-1B12R35,-1B21R35,-1B20R35,-1B5R35,-1A54B12S69B20S68A55B22S70B12S69A56"
				  "B19R36,-1B9R36,-1B29R36,-1B22R36,-1B37R36,-1B13R36,-1B10R36,-1B3R36,-1B20R36,-1B5R36,-1B11R36,-1B12R"
				  "36,-1B21R36,-1B4R36,-1B36R36,-1A57B29S71B5S8A58B19R37,-1B29R37,-1B37R37,-1B13R37,-1B3R37,-1B21R37,-1"
				  "B5R37,-1B4R37,-1B36R37,-1A59B19R38,-1B29R38,-1B22R38,-1B37R38,-1B13R38,-1B12R38,-1B3R38,-1B21R38,-1B"
				  "20R38,-1B5R38,-1B4R38,-1B36R38,-1A60B19R39,-1B29R39,-1B22R39,-1B37R39,-1B13R39,-1B12R39,-1B3R39,-1B2"
				  "1R39,-1B20R39,-1B5R39,-1B4R39,-1B36R39,-1A61B19R40,-1B29R40,-1B22R40,-1B37R40,-1B13R40,-1B12R40,-1B3"
				  "R40,-1B21R40,-1B20R40,-1B5R40,-1B4R40,-1B36R40,-1A62B19S37B35S35B29S39B37S41B13R41,-1B34S72B3R41,-1B"
				  "21S38B5S8B4R41,-1B36S36A63B0R42,-1B14R42,-1A64B16S74B29S73B5S8A65B3S75B7S22A66B0R43,-1B14S26B45S46A6"
				  "7B19R44,-1B22R44,-1B29R44,-1B37R44,-1B12R44,-1B21R44,-1B20R44,-1B5R44,-1A68B19R45,-1B9R45,-1B29R45,-"
				  "1B22R45,-1B37R45,-1B13R45,-1B10R45,-1B3R45,-1B20R45,-1B5R45,-1B11R45,-1B12R45,-1B21R45,-1B4R45,-1B36"
				  "R45,-1A69B19S37B29S39B37S41B21S38B5S8B36S53B40S76A70B19R46,-1B9R46,-1B29R46,-1B22R46,-1B37R46,-1B13R"
				  "46,-1B10R46,-1B3R46,-1B20R46,-1B5R46,-1B11R46,-1B12R46,-1B21R46,-1B4R46,-1B36R46,-1A71B19R47,-1B9R47"
				  ",-1B29R47,-1B22R47,-1B37R47,-1B13R47,-1B10R47,-1B3R47,-1B20R47,-1B5R47,-1B11R47,-1B12R47,-1B21R47,-1"
				  "B4R47,-1B36R47,-1A72B19S37B35S58B29S39B37S41B13R48,-1B3R48,-1B21S38B5S8B4R48,-1B36S36A73B15R49,-1A74"
				  "B15R50,-1A75B0R51,-1B14R51,-1B18R51,-1B44R51,-1B45R51,-1A76B19S37B29S39B22R52,-1B37S41B12R52,-1B21S3"
				  "8B20R52,-1B5S8B36S67"
			;

/*
	l_connect_symbol(connected_syms, GRO_SYM_⟧, symbol_provider, "⟧");
	l_connect_symbol(connected_syms, GRO_SYM_⊗, symbol_provider, "⊗");
	l_connect_symbol(connected_syms, GRO_SYM_SEMI, symbol_provider, "SEMI");
	l_connect_symbol(connected_syms, GRO_SYM_RULE_SEPERATOR, symbol_provider, "RULE_SEPERATOR");
	l_connect_symbol(connected_syms, GRO_SYM_IDENTIFIER, symbol_provider, "IDENTIFIER");
	l_connect_symbol(connected_syms, GRO_SYM_COLON, symbol_provider, "COLON");
	l_connect_symbol(connected_syms, GRO_SYM_COMMA, symbol_provider, "COMMA");
	l_connect_symbol(connected_syms, GRO_SYM_TERMINAL, symbol_provider, "TERMINAL");
	l_connect_symbol(connected_syms, GRO_SYM_STAR, symbol_provider, "STAR");
	l_connect_symbol(connected_syms, GRO_SYM_PLUS, symbol_provider, "PLUS");
	l_connect_symbol(connected_syms, GRO_SYM_EXCL, symbol_provider, "EXCL");
	l_connect_symbol(connected_syms, GRO_SYM_BAR, symbol_provider, "BAR");
	l_connect_symbol(connected_syms, GRO_SYM_INDEX_MARK, symbol_provider, "INDEX_MARK");
	l_connect_symbol(connected_syms, GRO_SYM_CODE, symbol_provider, "CODE");
	l_connect_symbol(connected_syms, GRO_SYM_CODE_TEXT, symbol_provider, "CODE_TEXT");
	l_connect_symbol(connected_syms, GRO_SYM_NUMBER, symbol_provider, "NUMBER");
	l_connect_symbol(connected_syms, GRO_SYM_IMPORTS, symbol_provider, "IMPORTS");
	l_connect_symbol(connected_syms, GRO_SYM_TYPE, symbol_provider, "TYPE");
	l_connect_symbol(connected_syms, GRO_SYM_LPAREN, symbol_provider, "LPAREN");
	l_connect_symbol(connected_syms, GRO_SYM_RPAREN, symbol_provider, "RPAREN");
	l_connect_symbol(connected_syms, GRO_SYM_LSQBRACK, symbol_provider, "LSQBRACK");
	l_connect_symbol(connected_syms, GRO_SYM_RSQBRACK, symbol_provider, "RSQBRACK");
	l_connect_symbol(connected_syms, GRO_SYM_LCUBRACK, symbol_provider, "LCUBRACK");
	l_connect_symbol(connected_syms, GRO_SYM_RCUBRACK, symbol_provider, "RCUBRACK");
	l_add_kw_mapping(priv->keyword_mapping, "⟧", GRO_SYM_⟧);
	l_add_kw_mapping(priv->keyword_mapping, "⊗", GRO_SYM_⊗);
	l_add_kw_mapping(priv->keyword_mapping, "semi", GRO_SYM_SEMI);
	l_add_kw_mapping(priv->keyword_mapping, "rule_seperator", GRO_SYM_RULE_SEPERATOR);
	l_add_kw_mapping(priv->keyword_mapping, "identifier", GRO_SYM_IDENTIFIER);
	l_add_kw_mapping(priv->keyword_mapping, "colon", GRO_SYM_COLON);
	l_add_kw_mapping(priv->keyword_mapping, "comma", GRO_SYM_COMMA);
	l_add_kw_mapping(priv->keyword_mapping, "terminal", GRO_SYM_TERMINAL);
	l_add_kw_mapping(priv->keyword_mapping, "star", GRO_SYM_STAR);
	l_add_kw_mapping(priv->keyword_mapping, "plus", GRO_SYM_PLUS);
	l_add_kw_mapping(priv->keyword_mapping, "excl", GRO_SYM_EXCL);
	l_add_kw_mapping(priv->keyword_mapping, "bar", GRO_SYM_BAR);
	l_add_kw_mapping(priv->keyword_mapping, "index_mark", GRO_SYM_INDEX_MARK);
	l_add_kw_mapping(priv->keyword_mapping, "code", GRO_SYM_CODE);
	l_add_kw_mapping(priv->keyword_mapping, "code_text", GRO_SYM_CODE_TEXT);
	l_add_kw_mapping(priv->keyword_mapping, "number", GRO_SYM_NUMBER);
	l_add_kw_mapping(priv->keyword_mapping, "imports", GRO_SYM_IMPORTS);
	l_add_kw_mapping(priv->keyword_mapping, "type", GRO_SYM_TYPE);
	l_add_kw_mapping(priv->keyword_mapping, "lparen", GRO_SYM_LPAREN);
	l_add_kw_mapping(priv->keyword_mapping, "rparen", GRO_SYM_RPAREN);
	l_add_kw_mapping(priv->keyword_mapping, "lsqbrack", GRO_SYM_LSQBRACK);
	l_add_kw_mapping(priv->keyword_mapping, "rsqbrack", GRO_SYM_RSQBRACK);
	l_add_kw_mapping(priv->keyword_mapping, "lcubrack", GRO_SYM_LCUBRACK);
	l_add_kw_mapping(priv->keyword_mapping, "rcubrack", GRO_SYM_RCUBRACK);
#define GRO_SYM_⟧                                                                                   0
#define GRO_SYM_⊗                                                                                   1
#define GRO_SYM_SEMI                                                                                2
#define GRO_SYM_RULE_SEPERATOR                                                                      3
#define GRO_SYM_IDENTIFIER                                                                          4
#define GRO_SYM_COLON                                                                               5
#define GRO_SYM_COMMA                                                                               6
#define GRO_SYM_TERMINAL                                                                            7
#define GRO_SYM_STAR                                                                                8
#define GRO_SYM_PLUS                                                                                9
#define GRO_SYM_EXCL                                                                                10
#define GRO_SYM_BAR                                                                                 11
#define GRO_SYM_INDEX_MARK                                                                          12
#define GRO_SYM_CODE                                                                                13
#define GRO_SYM_CODE_TEXT                                                                           14
#define GRO_SYM_NUMBER                                                                              15
#define GRO_SYM_IMPORTS                                                                             16
#define GRO_SYM_TYPE                                                                                17
#define GRO_SYM_LPAREN                                                                              18
#define GRO_SYM_RPAREN                                                                              19
#define GRO_SYM_LSQBRACK                                                                            20
#define GRO_SYM_RSQBRACK                                                                            21
#define GRO_SYM_LCUBRACK                                                                            22
#define GRO_SYM_RCUBRACK                                                                            23
*/
