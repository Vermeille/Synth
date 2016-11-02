#include <fstream>
#include "params.hh"
#include "wav_export.hh"

WavExporter::WavExporter(MonoSource* src)
    : src_(src)
{
}

void WavExporter::MkWav(const std::string& path, float duration)
{
    std::ofstream wav(path, std::ios::binary);
    uint32_t samples = duration * 44100;

    const uint32_t decl_size = 12;
    const uint32_t fmt_size = 24;
    const uint32_t data_size = 8;

    // declaration
    wav.write("RIFF", 4);
    uint32_t data32 = samples + data_size + fmt_size + decl_size - 8;
    wav.write((const char*)&data32, 4);
    wav.write("WAVE", 4);

    // fmt
    wav.write("fmt ", 4);
    data32 = fmt_size - 8;
    wav.write((const char*)&data32, 4);

    uint16_t data16 = 1;
    wav.write((const char*)&data16, 2);
    wav.write((const char*)&data16, 2);
    data32 = 44100;
    wav.write((const char*)&data32, 4);
    data32 = 88200;
    wav.write((const char*)&data32, 4);
    data16 = 2;
    wav.write((const char*)&data16, 2);
    data16 = 16;
    wav.write((const char*)&data16, 2);

    // data
    wav.write("data", 4);
    data32 = samples * 2;
    wav.write((const char*)&data32, 4);

    for (int i = 0; i < samples; ++i)
    {
        data16 = Render<SInt16>(src_->Gen());
        wav.write((const char*)&data16, 2);
    }
}
