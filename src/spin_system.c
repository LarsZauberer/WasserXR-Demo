#include <WasserXR/ecs/Scene.h>

WXR_System_Groups wxr_groups_spin_system = 1;

WXR_System_Groups wxr_select_spin_system(const WXR_Scene *scene,
                                         const WXR_Entity entity) {
  size_t query = wxr_entity_get_component(scene, entity, "Spin_Component") &&
                 wxr_entity_get_component(scene, entity, "WXR_Transform");
  if (query) {
    return 0;
  }
  return -1;
}

void wxr_system_spin_system(WXR_Scene *scene, WXR_Entity **entities,
                            const size_t *groups) {
  const size_t num_entities = groups[0];
  for (size_t i = 0; i < num_entities; i++) {
    void *spinner =
        wxr_entity_get_component(scene, entities[0][i], "Spin_Component");
    void *transform =
        wxr_entity_get_component(scene, entities[0][i], "WXR_Transform");

    float rotation_y = *(float *)wxr_get(scene, transform, "ry");
    float spin_speed = *(float *)wxr_get(scene, spinner, "speed");

    rotation_y += spin_speed;

    wxr_set(scene, transform, "ry", &rotation_y);
  }
}
