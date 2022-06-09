#include "tree_sitter.h"

extern VALUE mTreeSitter;

VALUE cNode;

void node_free(TSNode *node) { free(node); }

TSNode *value_to_node(VALUE self) {
  TSNode *node;

  Data_Get_Struct(self, TSNode, node);

  return node;
}

VALUE new_node(const TSNode *node) {
  TSNode *ptr = (TSNode *)malloc(sizeof(TSNode));
  memcpy(ptr, node, sizeof(TSNode));
  return Data_Wrap_Struct(cNode, NULL, node_free, ptr);
}

VALUE node_type(VALUE self) {
  TSNode *node = value_to_node(self);

  return rb_str_new_cstr(ts_node_type(*node));
}

VALUE node_symbol(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_symbol(*node));
}

VALUE node_start_byte(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_start_byte(*node));
}

VALUE node_start_point(VALUE self) {
  TSNode *node = value_to_node(self);
  TSPoint point = ts_node_start_point(*node);

  return new_point(&point);
}

VALUE node_end_byte(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_end_byte(*node));
}

VALUE node_end_point(VALUE self) {
  TSNode *node = value_to_node(self);
  TSPoint point = ts_node_end_point(*node);

  return new_point(&point);
}

VALUE node_string(VALUE self) {
  TSNode *node = value_to_node(self);

  return rb_str_new_cstr(ts_node_string(*node));
}

VALUE node_is_null(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_is_null(*node) ? Qtrue : Qfalse;
}

VALUE node_is_named(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_is_named(*node) ? Qtrue : Qfalse;
}

VALUE node_is_missing(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_is_missing(*node) ? Qtrue : Qfalse;
}

VALUE node_is_extra(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_is_extra(*node) ? Qtrue : Qfalse;
}

VALUE node_has_changes(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_has_changes(*node) ? Qtrue : Qfalse;
}

VALUE node_has_error(VALUE self) {
  TSNode *node = value_to_node(self);

  return ts_node_has_error(*node) ? Qtrue : Qfalse;
}

VALUE node_parent(VALUE self) {
  TSNode *node = value_to_node(self);
  TSNode parent = ts_node_parent(*node);

  return new_node(&parent);
}

VALUE node_child(VALUE self, VALUE index) {
  TSNode *node = value_to_node(self);
  uint32_t idx = NUM2INT(index);
  TSNode child = ts_node_child(*node, idx);

  return new_node(&child);
}

VALUE node_field_name_for_child(VALUE self, VALUE index) {
  TSNode *node = value_to_node(self);
  uint32_t idx = NUM2INT(index);
  const char *name = ts_node_field_name_for_child(*node, idx);
  if (name == NULL) {
    return Qnil;
  } else {
    return rb_str_new_cstr(name);
  }
}

VALUE node_child_count(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_child_count(*node));
}

VALUE node_named_child(VALUE self, VALUE index) {
  TSNode *node = value_to_node(self);
  uint32_t idx = NUM2INT(index);
  TSNode child = ts_node_named_child(*node, idx);

  return new_node(&child);
}

VALUE node_named_child_count(VALUE self) {
  TSNode *node = value_to_node(self);

  return INT2NUM(ts_node_named_child_count(*node));
}

VALUE node_child_by_field_name(VALUE self, VALUE field_name) {
  TSNode *node = value_to_node(self);
  const char *name = StringValuePtr(field_name);
  uint32_t length = (uint32_t)RSTRING_LEN(field_name);
  TSNode child = ts_node_child_by_field_name(*node, name, length);

  return new_node(&child);
}

VALUE node_child_by_field_id(VALUE self, VALUE field_id) {
  TSNode *node = value_to_node(self);
  uint16_t id = (uint16_t)NUM2INT(field_id);
  TSNode child = ts_node_child_by_field_id(*node, id);

  return new_node(&child);
}

VALUE node_next_sibling(VALUE self) {
  TSNode *node = value_to_node(self);
  TSNode sibling = ts_node_next_sibling(*node);

  return new_node(&sibling);
}

VALUE node_prev_sibling(VALUE self) {
  TSNode *node = value_to_node(self);
  TSNode sibling = ts_node_prev_sibling(*node);

  return new_node(&sibling);
}

VALUE node_next_named_sibling(VALUE self) {
  TSNode *node = value_to_node(self);
  TSNode sibling = ts_node_next_named_sibling(*node);

  return new_node(&sibling);
}

VALUE node_prev_named_sibling(VALUE self) {
  TSNode *node = value_to_node(self);
  TSNode sibling = ts_node_prev_named_sibling(*node);

  return new_node(&sibling);
}

VALUE node_first_child_for_byte(VALUE self, VALUE byte) {
  TSNode *node = value_to_node(self);
  uint32_t b = NUM2INT(byte);
  TSNode child = ts_node_first_child_for_byte(*node, b);

  return new_node(&child);
}

VALUE node_first_named_child_for_byte(VALUE self, VALUE byte) {
  TSNode *node = value_to_node(self);
  uint32_t b = NUM2INT(byte);
  TSNode child = ts_node_first_named_child_for_byte(*node, b);

  return new_node(&child);
}

VALUE node_descendant_for_byte_range(VALUE self, VALUE from, VALUE to) {
  TSNode *node = value_to_node(self);
  uint32_t f = NUM2INT(from);
  uint32_t t = NUM2INT(to);
  TSNode child = ts_node_descendant_for_byte_range(*node, f, t);

  return new_node(&child);
}

void init_node(void) {
  cNode = rb_define_class_under(mTreeSitter, "Node", rb_cObject);

  /* Class methods */
  rb_define_method(cNode, "type", node_type, 0);
  rb_define_method(cNode, "symbol", node_symbol, 0);
  rb_define_method(cNode, "start_byte", node_start_byte, 0);
  rb_define_method(cNode, "start_point", node_start_point, 0);
  rb_define_method(cNode, "end_byte", node_end_byte, 0);
  rb_define_method(cNode, "end_point", node_end_point, 0);
  rb_define_method(cNode, "string", node_string, 0);
  rb_define_method(cNode, "to_s", node_string, 0);
  rb_define_method(cNode, "null?", node_is_null, 0);
  rb_define_method(cNode, "named?", node_is_null, 0);
  rb_define_method(cNode, "missing?", node_is_missing, 0);
  rb_define_method(cNode, "extra?", node_is_extra, 0);
  rb_define_method(cNode, "changes?", node_has_changes, 0);
  rb_define_method(cNode, "error?", node_has_error, 0);
  rb_define_method(cNode, "parent", node_parent, 0);
  rb_define_method(cNode, "child", node_child, 1);
  rb_define_method(cNode, "field_name_for_child", node_field_name_for_child, 1);
  rb_define_method(cNode, "child_count", node_child_count, 0);
  rb_define_method(cNode, "named_child", node_named_child, 1);
  rb_define_method(cNode, "named_child_count", node_named_child_count, 0);
  rb_define_method(cNode, "child_by_field_name", node_child_by_field_name, 1);
  rb_define_method(cNode, "child_by_field_id", node_child_by_field_id, 1);
  rb_define_method(cNode, "next_sibling", node_next_sibling, 0);
  rb_define_method(cNode, "prev_sibling", node_prev_sibling, 0);
  rb_define_method(cNode, "next_named_sibling", node_next_named_sibling, 0);
  rb_define_method(cNode, "prev_named_sibling", node_prev_named_sibling, 0);
  rb_define_method(cNode, "first_child_for_byte", node_first_child_for_byte, 1);
  rb_define_method(cNode, "first_named_child_for_byte",
                   node_first_child_for_byte, 1);
  rb_define_method(cNode, "descendant_for_byte_range",
                   node_descendant_for_byte_range, 2);
}
