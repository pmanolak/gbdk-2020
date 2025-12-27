    .include    "global.s"

    .area   GBDKOVR (PAG, OVR)
    .fill_bkg_rect_padding::    .ds 4   ; Padding to avoid clash with _set_bkg_tile_xy vars
    _fill_bkg_rect_PARM_3::     .ds 1
    _fill_bkg_rect_PARM_4::     .ds 1
    _fill_bkg_rect_PARM_5::     .ds 1
    .xpos:                      .ds 1
    .ypos:                      .ds 1
    .xpos_save:                 .ds 1
    .width_save:                .ds 1

    .area   _HOME

_fill_bkg_rect::
    .define .width  "_fill_bkg_rect_PARM_3"
    .define .height "_fill_bkg_rect_PARM_4"
    .define .tile   "_fill_bkg_rect_PARM_5"
    sta *.xpos
    sta *.xpos_save
    stx *.ypos
    lda *.width
    sta *.width_save
    lda *.tile
    sta *_set_bkg_tile_xy_PARM_3
1$:
    lda *.xpos
    and #.DEVICE_SCREEN_BUFFER_WIDTH-1
    ldx *.ypos
    jsr _set_bkg_tile_xy
    inc *.xpos
    dec *.width
    bne 1$
    lda *.xpos_save
    sta *.xpos
    lda *.width_save
    sta *.width
    inc *.ypos
    lda *.ypos
    cmp #.DEVICE_SCREEN_BUFFER_HEIGHT
    bne 0$
    lda #0
0$:
    sta *.ypos
    dec *.height
    bne 1$
    rts
