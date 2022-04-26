std::int32_t main(
    const std::int32_t argc,
    const char**       argv
)
{
    if( argc < 2 ) {
        printf( R"(usage:
    executable.exe "SuperCoolGameTitle" // ENTER YOUR APPLICATION TITLE (FORTNITE HWND NAME) FN HWND NAME = FortniteClient-Win64-Shipping.exe
)" );
        return -1;
    }

    const auto overlay = std::make_unique<aero::overlay>();
    const auto status  = overlay->attach( argv[ 1 ] );

    if( status != aero::api_status::success ) {
        printf( "[>] failed to create overlay: %d\n", status );
        return -1;
    }

    const auto surface = overlay->get_surface();
    const auto font    = surface->add_font( "test", "Verdana", 12.f );

    surface->add_callback([&surface, &font]
    {
        surface->text( 5.f, 5.f, font, 0xFFFFFFFF, "ROKA OVERLAY" );
    } );

    while( overlay->message_loop() ) {
        if( surface->begin_scene() ) {
            surface->end_scene();
        }

        std::this_thread::sleep_for( std::chrono::milliseconds( 2 ) );
    }
};
