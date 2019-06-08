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
				  "r30,1p11r29,1p9r26,2,0p3r25,2,0p2r28,1p8r32,1p14r33,2,1p15r26,2p3r25,2p2r25,5,0,3,4p1r30,2p10r27,3p5"
				  "r27,3p6r31,3p12r32,2p13r36,1p20r34,2,0p17r33,2p15r37,2,1p26r35,1p19r25,5,3,4p1r47,1p43r41,2p33r44,2,"
				  "0p37r25,5,0,3p1r25,5,0,4p1r42,2,0p34r28,3p7r33,4,3p16r36,2p22r36,2p23r36,2p21r39,1p30r40,1p32r34,2p1"
				  "7r37,2p26r25,5,3p1r25,5,4p1r44,2p37r46,1p40r25,5,0p1r42,2p34r33,4p16r40,2p31r37,3p24r38,2p27r37,3p25"
				  "r25,5p1r45,3p39r39,3p29r46,3p41r46,3p42r43,4p36A0B8S3B27S4B26S6B25S8B29S5B30S7B31S1B5S2A1B29R0,-1B0R"
				  "0,-1B17R0,-1B5R0,-1A2B4R1,-1B11R1,-1B20R1,-1B7R1,-1B21R1,-1B36R1,-1B9R1,-1B13R1,-1B15R1,-1B3R1,-1B19"
				  "R1,-1B6R1,-1B10R1,-1B5R1,-1B33R1,-1B32R1,-1B29R1,-1B28R1,-1B12R1,-1B37R1,-1B22R1,-1A3B29S9B28S10B1S1"
				  "1B5S2A4B8R2,-1B29R2,-1B30R2,-1B31R2,-1B5R2,-1A5B33S14B4S15B32S13B13S12A6B8S3B27S16B29S5B30S17B31S1B5"
				  "S2A7B29S5B0R3,-1B17S18B41S19B31S20B5S2A8B0EA9B7R4,-1B3R4,-1A10B7S22B3S21A11B3S23A12B29S24B5S2A13B33S"
				  "26B4S15B13S12B3S25A14B4R5,-1B13R5,-1B3R5,-1A15B4R6,-1B34S30B29S31B36S32B21S33B37S27B35S28B13R6,-1B3R"
				  "6,-1B19S29B5S2A16B8R7,-1B29R7,-1B30R7,-1B31R7,-1B5R7,-1A17B29S5B0R8,-1B17S18B41S34B31S20B5S2A18B15S3"
				  "5B47S36A19B43S42B0R9,-1B45S37B42S40B44S38B14S39B18S41A20B29R10,-1B0R10,-1B17R10,-1B5R10,-1A21B8R11,-"
				  "1B29R11,-1B30R11,-1B31R11,-1B5R11,-1A22B29S43B5S2A23B8R12,-1B29R12,-1B30R12,-1B31R12,-1B5R12,-1A24B4"
				  "S44A25B29R13,-1B0R13,-1B17R13,-1B5R13,-1A26B4R14,-1B13R14,-1B3R14,-1A27B4R15,-1B11S46B20R15,-1B21R15"
				  ",-1B36R15,-1B9S47B13R15,-1B3R15,-1B19R15,-1B10S45B5R15,-1B29R15,-1B12R15,-1B37R15,-1B22R15,-1A28B4R1"
				  "6,-1B36R16,-1B21R16,-1B29R16,-1B37R16,-1B13R16,-1B3R16,-1B19R16,-1B5R16,-1A29B39S49B29S31B36S50B21S3"
				  "3B37S27B19S29B40S48B5S2A30B4R17,-1B29S31B36S32B21S33B37S27B35S51B13R17,-1B3R17,-1B19S29B5S2A31B4R18,"
				  "-1B11R18,-1B20R18,-1B21R18,-1B36R18,-1B38S53B9R18,-1B13R18,-1B3R18,-1B19R18,-1B6S52B10R18,-1B5R18,-1"
				  "B29R18,-1B12R18,-1B37R18,-1B22R18,-1A32B4R19,-1B36R19,-1B21R19,-1B29R19,-1B37R19,-1B13R19,-1B3R19,-1"
				  "B19R19,-1B5R19,-1A33B39S54B29S31B36S50B21S33B37S27B19S29B40S48B5S2A34B43S42B0R20,-1B45S37B42S56B44S5"
				  "5B14S39B18S41A35B43R21,-1B0R21,-1B45R21,-1B42R21,-1B44R21,-1B14R21,-1B18R21,-1A36B43R22,-1B0R22,-1B4"
				  "5R22,-1B42R22,-1B44R22,-1B14R22,-1B18R22,-1A37B0R23,-1B14R23,-1A38B0R24,-1B45S57B14S39A39B46S58B29S5"
				  "9B5S2A40B43S61B0R25,-1B45S37B44S60B14S39B18S41A41B29S62B5S2A42B0R26,-1B45R26,-1B44R26,-1B14R26,-1B18"
				  "R26,-1A43B7R27,-1B3R27,-1A44B4R28,-1B34S63B29S31B36S32B21S33B37S27B35S28B13R28,-1B3R28,-1B19S29B5S2A"
				  "45B4R29,-1B20R29,-1B21R29,-1B29R29,-1B36R29,-1B12R29,-1B37R29,-1B13R29,-1B22R29,-1B3R29,-1B19R29,-1B"
				  "5R29,-1A46B4R30,-1B20R30,-1B21R30,-1B29R30,-1B36R30,-1B12R30,-1B37R30,-1B13R30,-1B22R30,-1B3R30,-1B1"
				  "9R30,-1B5R30,-1A47B4R31,-1B20R31,-1B21R31,-1B29R31,-1B36R31,-1B12R31,-1B37R31,-1B13R31,-1B22R31,-1B3"
				  "R31,-1B19R31,-1B5R31,-1A48B20R32,-1B29S31B36S64B21S33B12R32,-1B37S27B22R32,-1B19S29B5S2A49B20S65B12S"
				  "66A50B20R33,-1B21R33,-1B29R33,-1B12R33,-1B37R33,-1B22R33,-1B19R33,-1B5R33,-1A51B4R34,-1B36R34,-1B21R"
				  "34,-1B29R34,-1B37R34,-1B13R34,-1B3R34,-1B19R34,-1B5R34,-1A52B29S67B5S2A53B4R35,-1B11R35,-1B20R35,-1B"
				  "21R35,-1B36R35,-1B9R35,-1B13R35,-1B3R35,-1B19R35,-1B10R35,-1B5R35,-1B29R35,-1B12R35,-1B37R35,-1B22R3"
				  "5,-1A54B12S66B22S68A55B0R36,-1B45S57B14S39A56B43S61B0R37,-1B45S37B44S69B14S39B18S41A57B0R38,-1B14R38"
				  ",-1A58B15S35B47S70A59B13S71B15R39,-1A60B0R40,-1B45S57B14S39A61B0R41,-1B45R41,-1B44R41,-1B14R41,-1B18"
				  "R41,-1A62B29S9B28S72B5S2A63B4R42,-1B29S31B36S32B21S33B37S27B35S51B13R42,-1B3R42,-1B19S29B5S2A64B20R4"
				  "3,-1B21R43,-1B29R43,-1B12R43,-1B37R43,-1B22R43,-1B19R43,-1B5R43,-1A65B4R44,-1B11R44,-1B20R44,-1B21R4"
				  "4,-1B36R44,-1B9R44,-1B13R44,-1B3R44,-1B19R44,-1B10R44,-1B5R44,-1B29R44,-1B12R44,-1B37R44,-1B22R44,-1"
				  "A66B29S31B36S50B21S33B37S27B19S29B40S73B5S2A67B4R45,-1B11R45,-1B20R45,-1B21R45,-1B36R45,-1B9R45,-1B1"
				  "3R45,-1B3R45,-1B19R45,-1B10R45,-1B5R45,-1B29R45,-1B12R45,-1B37R45,-1B22R45,-1A68B4R46,-1B11R46,-1B20"
				  "R46,-1B21R46,-1B36R46,-1B9R46,-1B13R46,-1B3R46,-1B19R46,-1B10R46,-1B5R46,-1B29R46,-1B12R46,-1B37R46,"
				  "-1B22R46,-1A69B0R47,-1B45S57B14S39A70B0R48,-1B14R48,-1A71B29S74B16S75B5S2A72B7S22B3S76A73B20R49,-1B2"
				  "9S31B36S64B21S33B12R49,-1B37S27B22R49,-1B19S29B5S2A74B15R50,-1A75B15R51,-1A76B0R52,-1B45R52,-1B44R52"
				  ",-1B14R52,-1B18R52,-1"
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
