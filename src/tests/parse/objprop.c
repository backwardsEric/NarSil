/* parse/objprop */
/* Exercise parsing used for object_property.txt. */

struct command;
#include "unit-test.h"
#include "datafile.h"
#include "init.h"
#include "object.h"
#include "obj-init.h"
#include "obj-slays.h"
#include "obj-smith.h"
#include "z-virt.h"

static char dummy_orc_slay[16] = "ORC_1";
static char dummy_spider_slay[16] = "SPIDER_1";
static struct slay dummy_slays[] = {
	{ .code = NULL },
	{ .code = dummy_orc_slay },
	{ .code = dummy_spider_slay },
};
static char dummy_cold_brand[16] = "COLD_1";
static char dummy_fire_brand[16] = "FIRE_1";
static struct brand dummy_brands[] = {
	{ .code = NULL },
	{ .code = dummy_cold_brand },
	{ .code = dummy_fire_brand },
};

int setup_tests(void **state) {
	*state = object_property_parser.init();
	/* Needed by object_property_parser.finish and slay/brand logic. */
	z_info = mem_zalloc(sizeof(*z_info));
	/* Do minimal setup for slays and brands. */
	z_info->slay_max = (uint8_t) N_ELEMENTS(dummy_slays);
	slays = dummy_slays;
	z_info->brand_max = (uint8_t) N_ELEMENTS(dummy_brands);
	brands = dummy_brands;
	return !*state;
}

int teardown_tests(void *state) {
	struct parser *p = (struct parser*) state;
	int r = 0;

	if (object_property_parser.finish(p)) {
		r = 1;
	}
	object_property_parser.cleanup();
	mem_free(z_info);
	return r;
}

static int test_missing_record_header0(void *state) {
	struct parser *p = (struct parser*) state;
	struct obj_property *prop = (struct obj_property*) parser_priv(p);
	enum parser_error r;

	null(prop);
	r = parser_parse(p, "type:flag");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "subtype:protection");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "id-type:on effect");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "code:PROT_FEAR");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "adjective:ugly");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "neg-adjective:handsome");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "msg:Your {name} glows.");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "slay-msg:cuts deeply");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "desc:testing");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "smith-cat:stat");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "smith-difficulty:12");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	r = parser_parse(p, "smith-cost:STR:1");
	eq(r, PARSE_ERROR_MISSING_RECORD_HEADER);
	ok;
}

static int test_name0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "name:test");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->name);
	require(streq(prop->name, "test"));
	eq(prop->type, 0);
	eq(prop->subtype, 0);
	eq(prop->id_type, 0);
	eq(prop->smith_cat, SMITH_CAT_MAX);
	eq(prop->smith_diff, 0);
	eq(prop->smith_cost_type, 0);
	eq(prop->smith_cost, 0);
	null(prop->adjective);
	null(prop->neg_adj);
	null(prop->msg);
	null(prop->slay_msg);
	null(prop->desc);
	ok;
}

static int test_type0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "type:stat");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->type, OBJ_PROPERTY_STAT);
	r = parser_parse(p, "type:skill");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_SKILL);
	r = parser_parse(p, "type:mod");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_MOD);
	r = parser_parse(p, "type:flag");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_FLAG);
	r = parser_parse(p, "type:slay");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_SLAY);
	r = parser_parse(p, "type:brand");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_BRAND);
	r = parser_parse(p, "type:ignore");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_IGNORE);
	r = parser_parse(p, "type:resistance");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_RESIST);
	r = parser_parse(p, "type:vulnerability");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->type, OBJ_PROPERTY_VULN);
	ok;
}

static int test_type_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "type:xyzzy");

	eq(r, PARSE_ERROR_INVALID_PROPERTY);
	ok;
}

static int test_subtype0(void *state) {
	struct parser *p = (struct parser*) state;
	/* Mark the property as a flag. */
	enum parser_error r = parser_parse(p, "type:flag");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "subtype:sustain");
	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->subtype, OFT_SUST);
	r = parser_parse(p, "subtype:protection");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->subtype, OFT_PROT);
	r = parser_parse(p, "subtype:misc ability");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->subtype, OFT_MISC);
	r = parser_parse(p, "subtype:basic");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->subtype, OFT_BASIC);
	r = parser_parse(p, "subtype:melee");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->subtype, OFT_MELEE);
	r = parser_parse(p, "subtype:bad");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->subtype, OFT_BAD);
	ok;
}

static int test_subtype_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "subtype:xyzzy");

	eq(r, PARSE_ERROR_INVALID_SUBTYPE);
	ok;
}

static int test_id_type0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "id-type:on effect");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->id_type, OFID_NORMAL);
	r = parser_parse(p, "id-type:timed");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->id_type, OFID_TIMED);
	r = parser_parse(p, "id-type:on wield");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->id_type, OFID_WIELD);
	ok;
}

static int test_id_type_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "id-type:xyzzy");

	eq(r, PARSE_ERROR_INVALID_ID_TYPE);
	ok;
}

static int test_code0(void *state) {
	struct parser *p = (struct parser*) state;
	/* Set up a type. */
	enum parser_error r = parser_parse(p, "type:stat");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:STR");
	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->index, OBJ_MOD_STR);

	r = parser_parse(p, "type:skill");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:STEALTH");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, OBJ_MOD_STEALTH);

	r = parser_parse(p, "type:mod");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:TUNNEL");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, OBJ_MOD_TUNNEL);

	r = parser_parse(p, "type:flag");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:PROT_FEAR");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, OF_PROT_FEAR);

	r = parser_parse(p, "type:slay");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:ORC_1");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, 1);

	r = parser_parse(p, "type:brand");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:FIRE_1");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, 2);

	r = parser_parse(p, "type:ignore");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:COLD");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, ELEM_COLD);

	r = parser_parse(p, "type:resistance");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:FIRE");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, ELEM_FIRE);

	r = parser_parse(p, "type:vulnerability");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:ACID");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->index, ELEM_ACID);

	ok;
}

static int test_code_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	/* Set up a type. */
	enum parser_error r = parser_parse(p, "type:stat");

	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:skill");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:mod");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:flag");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:slay");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:brand");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:ignore");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:resistance");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	r = parser_parse(p, "type:vulnerability");
	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:xyzzy");
	eq(r, PARSE_ERROR_INVALID_OBJ_PROP_CODE);

	ok;
}

static int test_smith_cat0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "smith-cat:stat");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->smith_cat, SMITH_CAT_STAT);

	r = parser_parse(p, "smith-cat:sustain");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_SUSTAIN);

	r = parser_parse(p, "smith-cat:skill");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_SKILL);

	r = parser_parse(p, "smith-cat:melee");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_MELEE);

	r = parser_parse(p, "smith-cat:slay");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_SLAY);

	r = parser_parse(p, "smith-cat:resist");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_RESIST);

	r = parser_parse(p, "smith-cat:curse");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_CURSE);

	r = parser_parse(p, "smith-cat:misc");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cat, SMITH_CAT_MISC);

	ok;
}

static int test_smith_cat_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "smith-cat:xyzzy");

	eq(r, PARSE_ERROR_INVALID_SMITHING_CATEGORY);
	ok;
}

static int test_smith_difficulty0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "smith-difficulty:12");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->smith_diff, 12);
	ok;
}

static int test_smith_cost0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "smith-cost:STR:2");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	eq(prop->smith_cost_type, SMITH_COST_STR);
	eq(prop->smith_cost, 2);

	r = parser_parse(p, "smith-cost:DEX:1");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cost_type, SMITH_COST_DEX);
	eq(prop->smith_cost, 1);

	r = parser_parse(p, "smith-cost:CON:3");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cost_type, SMITH_COST_CON);
	eq(prop->smith_cost, 3);

	r = parser_parse(p, "smith-cost:GRA:4");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cost_type, SMITH_COST_GRA);
	eq(prop->smith_cost, 4);

	r = parser_parse(p, "smith-cost:EXP:500");
	eq(r, PARSE_ERROR_NONE);
	eq(prop->smith_cost_type, SMITH_COST_EXP);
	eq(prop->smith_cost, 500);

	ok;
}

static int test_smith_cost_bad0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "smith-cost:XYZZY:8");

	eq(r, PARSE_ERROR_INVALID_SMITHING_COST_TYPE);
	ok;
}

static int test_adjective0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "adjective:weak");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->adjective);
	require(streq(prop->adjective, "weak"));
	/* Try setting again to see if memory is leaked. */
	r = parser_parse(p, "adjective:bland");
	eq(r, PARSE_ERROR_NONE);
	notnull(prop->adjective);
	require(streq(prop->adjective, "bland"));
	ok;
}

static int test_neg_adjective0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "neg-adjective:opulent");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->neg_adj);
	require(streq(prop->neg_adj, "opulent"));
	/* Try setting again to see if memory is leaked. */
	r = parser_parse(p, "neg-adjective:wretched");
	eq(r, PARSE_ERROR_NONE);
	notnull(prop->neg_adj);
	require(streq(prop->neg_adj, "wretched"));
	ok;
}

static int test_msg0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "msg:Your {name} glows.");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->msg);
	require(streq(prop->msg, "Your {name} glows."));
	/* Try setting again to see if memory is leaked. */
	r = parser_parse(p, "msg:Your {name} shudders.");
	eq(r, PARSE_ERROR_NONE);
	notnull(prop->msg);
	require(streq(prop->msg, "Your {name} shudders."));
	ok;
}

static int test_slay_msg0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "slay-msg:cuts deeply");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->slay_msg);
	require(streq(prop->slay_msg, "cuts deeply"));
	/* Try setting again to see if memory is leaked. */
	r = parser_parse(p, "slay-msg:drains life from {name}");
	eq(r, PARSE_ERROR_NONE);
	notnull(prop->slay_msg);
	require(streq(prop->slay_msg, "drains life from {name}"));
	ok;
}

static int test_desc0(void *state) {
	struct parser *p = (struct parser*) state;
	enum parser_error r = parser_parse(p, "desc:confusion");
	struct obj_property *prop;

	eq(r, PARSE_ERROR_NONE);
	prop = (struct obj_property*) parser_priv(p);
	notnull(prop);
	notnull(prop->desc);
	require(streq(prop->desc, "confusion"));
	/* Try setting again to see if memory is leaked. */
	r = parser_parse(p, "desc:fear");
	eq(r, PARSE_ERROR_NONE);
	notnull(prop->desc);
	require(streq(prop->desc, "fear"));
	ok;
}

static int test_missing_type0(void *state) {
	struct parser *p = (struct parser*) state;
	/* Set up a property without a type. */
	enum parser_error r = parser_parse(p, "name:test2");

	eq(r, PARSE_ERROR_NONE);
	r = parser_parse(p, "code:ACID");
	eq(r, PARSE_ERROR_MISSING_OBJ_PROP_TYPE);
	ok;
}

const char *suite_name = "parse/objprop";
/*
 * test_missing_record_header0() has to be before test_name0() and
 * test_missing_type0().
 */
struct test tests[] = {
	{ "missing_record_header0", test_missing_record_header0 },
	{ "name0", test_name0 },
	{ "type0", test_type0 },
	{ "type_bad0", test_type_bad0 },
	{ "subtype0", test_subtype0 },
	{ "subtype_bad0", test_subtype_bad0 },
	{ "id_type0", test_id_type0 },
	{ "id_type_bad0", test_id_type_bad0 },
	{ "code0", test_code0 },
	{ "code_bad0", test_code_bad0 },
	{ "smith_cat0", test_smith_cat0 },
	{ "smith_cat_bad0", test_smith_cat_bad0 },
	{ "smith_difficulty0", test_smith_difficulty0 },
	{ "smith_cost0", test_smith_cost0 },
	{ "smith_cost_bad0", test_smith_cost_bad0 },
	{ "adjective0", test_adjective0 },
	{ "neg_adjective0", test_neg_adjective0 },
	{ "msg0", test_msg0 },
	{ "slay_msg0", test_slay_msg0 },
	{ "desc0", test_desc0 },
	{ "missing_type0", test_missing_type0 },
	{ NULL, NULL }
};
