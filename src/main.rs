use wasserxr::scene::{Scene, logging::file_logger};

#[cfg(feature = "static")]
use wasserxr_core as _;

fn main() {
    let mut scene = Scene::new();
    scene.register_callback_logger(file_logger);

    #[cfg(not(feature = "static"))]
    {
        scene
            .load_plugin("libwasserxr_core.so".to_owned())
            .expect("Failed to load core plugin");
    }

    scene
        .add_system("console".to_owned(), 100)
        .expect("Failed to add system `console`");

    let _ = scene.load("./scenes/monkey.wxr");

    while scene.tick() {}
    let _ = scene.reset();
}
