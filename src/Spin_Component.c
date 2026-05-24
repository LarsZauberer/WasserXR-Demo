#include <WasserXR/ecs/Macros.h>
#include <WasserXR/ecs/Scene.h>
#include <stdlib.h>

typedef struct Spin_Component {
  float speed;
} Spin_Component;

void *wxr_create_Spin_Component() {
  Spin_Component *component = malloc(sizeof(Spin_Component));
  component->speed = 1.0F;
  return component;
}

void wxr_destroy_Spin_Component(void *component) { free(component); }

WXR_BASIC_ACCESS(Spin_Component, speed, &component->speed, sizeof(float));
WXR_BASIC_SERIALIZERS(Spin_Component, speed, &component->speed, sizeof(float));

void wxr_schema_Spin_Component(WXR_Component_Schema *schema) {
  WXR_SCHEMA_FIELD_FULL(Spin_Component, WXR_F, speed);
}
