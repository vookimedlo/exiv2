//Riff Video - Detection And Display

#include "riffvideo.hpp"
#include "futils.hpp"
#include "basicio.hpp"
#include "tags.hpp"
#include "tags_int.hpp"
#include "types.hpp"

namespace Exiv2 {
    namespace Internal {

    extern const TagDetails audioEncodingValues[] =  {
        {   0x1, "Microsoft PCM" },
        {   0x2, "Microsoft ADPCM" },
        {   0x3, "Microsoft IEEE float" },
        {   0x4, "Compaq VSELP" },
        {   0x5, "IBM CVSD" },
        {   0x6, "Microsoft a-Law" },
        {   0x7, "Microsoft u-Law" },
        {   0x8, "Microsoft DTS" },
        {   0x9, "DRM" },
        {   0xa, "WMA 9 Speech" },
        {   0xb, "Microsoft Windows Media RT Voice" },
        {   0x10, "OKI-ADPCM" },
        {   0x11, "Intel IMA/DVI-ADPCM" },
        {   0x12, "Videologic Mediaspace ADPCM" },
        {   0x13, "Sierra ADPCM" },
        {   0x14, "Antex G.723 ADPCM" },
        {   0x15, "DSP Solutions DIGISTD" },
        {   0x16, "DSP Solutions DIGIFIX" },
        {   0x17, "Dialoic OKI ADPCM" },
        {   0x18, "Media Vision ADPCM" },
        {   0x19, "HP CU" },
        {   0x1a, "HP Dynamic Voice" },
        {   0x20, "Yamaha ADPCM" },
        {   0x21, "SONARC Speech Compression" },
        {   0x22, "DSP Group True Speech" },
        {   0x23, "Echo Speech Corp." },
        {   0x24, "Virtual Music Audiofile AF36" },
        {   0x25, "Audio Processing Tech." },
        {   0x26, "Virtual Music Audiofile AF10" },
        {   0x27, "Aculab Prosody 1612" },
        {   0x28, "Merging Tech. LRC" },
        {   0x30, "Dolby AC2" },
        {   0x31, "Microsoft GSM610" },
        {   0x32, "MSN Audio" },
        {   0x33, "Antex ADPCME" },
        {   0x34, "Control Resources VQLPC" },
        {   0x35, "DSP Solutions DIGIREAL" },
        {   0x36, "DSP Solutions DIGIADPCM" },
        {   0x37, "Control Resources CR10" },
        {   0x38, "Natural MicroSystems VBX ADPCM" },
        {   0x39, "Crystal Semiconductor IMA ADPCM" },
        {   0x3a, "Echo Speech ECHOSC3" },
        {   0x3b, "Rockwell ADPCM" },
        {   0x3c, "Rockwell DIGITALK" },
        {   0x3d, "Xebec Multimedia" },
        {   0x40, "Antex G.721 ADPCM" },
        {   0x41, "Antex G.728 CELP" },
        {   0x42, "Microsoft MSG723" },
        {   0x43, "IBM AVC ADPCM" },
        {   0x45, "ITU-T G.726" },
        {   0x50, "Microsoft MPEG" },
        {   0x51, "RT23 or PAC" },
        {   0x52, "InSoft RT24" },
        {   0x53, "InSoft PAC" },
        {   0x55, "MP3" },
        {   0x59, "Cirrus" },
        {   0x60, "Cirrus Logic" },
        {   0x61, "ESS Tech. PCM" },
        {   0x62, "Voxware Inc." },
        {   0x63, "Canopus ATRAC" },
        {   0x64, "APICOM G.726 ADPCM" },
        {   0x65, "APICOM G.722 ADPCM" },
        {   0x66, "Microsoft DSAT" },
        {   0x67, "Micorsoft DSAT DISPLAY" },
        {   0x69, "Voxware Byte Aligned" },
        {   0x70, "Voxware AC8" },
        {   0x71, "Voxware AC10" },
        {   0x72, "Voxware AC16" },
        {   0x73, "Voxware AC20" },
        {   0x74, "Voxware MetaVoice" },
        {   0x75, "Voxware MetaSound" },
        {   0x76, "Voxware RT29HW" },
        {   0x77, "Voxware VR12" },
        {   0x78, "Voxware VR18" },
        {   0x79, "Voxware TQ40" },
        {   0x7a, "Voxware SC3" },
        {   0x7b, "Voxware SC3" },
        {   0x80, "Soundsoft" },
        {   0x81, "Voxware TQ60" },
        {   0x82, "Microsoft MSRT24" },
        {   0x83, "AT&T G.729A" },
        {   0x84, "Motion Pixels MVI MV12" },
        {   0x85, "DataFusion G.726" },
        {   0x86, "DataFusion GSM610" },
        {   0x88, "Iterated Systems Audio" },
        {   0x89, "Onlive" },
        {   0x8a, "Multitude, Inc. FT SX20" },
        {   0x8b, "Infocom ITS A/S G.721 ADPCM" },
        {   0x8c, "Convedia G729" },
        {   0x8d, "Not specified congruency, Inc." },
        {   0x91, "Siemens SBC24" },
        {   0x92, "Sonic Foundry Dolby AC3 APDIF" },
        {   0x93, "MediaSonic G.723" },
        {   0x94, "Aculab Prosody 8kbps" },
        {   0x97, "ZyXEL ADPCM" },
        {   0x98, "Philips LPCBB" },
        {   0x99, "Studer Professional Audio Packed" },
        {   0xa0, "Malden PhonyTalk" },
        {   0xa1, "Racal Recorder GSM" },
        {   0xa2, "Racal Recorder G720.a" },
        {   0xa3, "Racal G723.1" },
        {   0xa4, "Racal Tetra ACELP" },
        {   0xb0, "NEC AAC NEC Corporation" },
        {   0xff, "AAC" },
        {   0x100, "Rhetorex ADPCM" },
        {   0x101, "IBM u-Law" },
        {   0x102, "IBM a-Law" },
        {   0x103, "IBM ADPCM" },
        {   0x111, "Vivo G.723" },
        {   0x112, "Vivo Siren" },
        {   0x120, "Philips Speech Processing CELP" },
        {   0x121, "Philips Speech Processing GRUNDIG" },
        {   0x123, "Digital G.723" },
        {   0x125, "Sanyo LD ADPCM" },
        {   0x130, "Sipro Lab ACEPLNET" },
        {   0x131, "Sipro Lab ACELP4800" },
        {   0x132, "Sipro Lab ACELP8V3" },
        {   0x133, "Sipro Lab G.729" },
        {   0x134, "Sipro Lab G.729A" },
        {   0x135, "Sipro Lab Kelvin" },
        {   0x136, "VoiceAge AMR" },
        {   0x140, "Dictaphone G.726 ADPCM" },
        {   0x150, "Qualcomm PureVoice" },
        {   0x151, "Qualcomm HalfRate" },
        {   0x155, "Ring Zero Systems TUBGSM" },
        {   0x160, "Microsoft Audio1" },
        {   0x161, "Windows Media Audio V2 V7 V8 V9 / DivX audio (WMA) / Alex AC3 Audio" },
        {   0x162, "Windows Media Audio Professional V9" },
        {   0x163, "Windows Media Audio Lossless V9" },
        {   0x164, "WMA Pro over S/PDIF" },
        {   0x170, "UNISYS NAP ADPCM" },
        {   0x171, "UNISYS NAP ULAW" },
        {   0x172, "UNISYS NAP ALAW" },
        {   0x173, "UNISYS NAP 16K" },
        {   0x174, "MM SYCOM ACM SYC008 SyCom Technologies" },
        {   0x175, "MM SYCOM ACM SYC701 G726L SyCom Technologies" },
        {   0x176, "MM SYCOM ACM SYC701 CELP54 SyCom Technologies" },
        {   0x177, "MM SYCOM ACM SYC701 CELP68 SyCom Technologies" },
        {   0x178, "Knowledge Adventure ADPCM" },
        {   0x180, "Fraunhofer IIS MPEG2AAC" },
        {   0x190, "Digital Theater Systems DTS DS" },
        {   0x200, "Creative Labs ADPCM" },
        {   0x202, "Creative Labs FASTSPEECH8" },
        {   0x203, "Creative Labs FASTSPEECH10" },
        {   0x210, "UHER ADPCM" },
        {   0x215, "Ulead DV ACM" },
        {   0x216, "Ulead DV ACM" },
        {   0x220, "Quarterdeck Corp." },
        {   0x230, "I-Link VC" },
        {   0x240, "Aureal Semiconductor Raw Sport" },
        {   0x241, "ESST AC3" },
        {   0x250, "Interactive Products HSX" },
        {   0x251, "Interactive Products RPELP" },
        {   0x260, "Consistent CS2" },
        {   0x270, "Sony SCX" },
        {   0x271, "Sony SCY" },
        {   0x272, "Sony ATRAC3" },
        {   0x273, "Sony SPC" },
        {   0x280, "TELUM Telum Inc." },
        {   0x281, "TELUMIA Telum Inc." },
        {   0x285, "Norcom Voice Systems ADPCM" },
        {   0x300, "Fujitsu FM TOWNS SND" },
        {   0x301, "Fujitsu (not specified)" },
        {   0x302, "Fujitsu (not specified)" },
        {   0x303, "Fujitsu (not specified)" },
        {   0x304, "Fujitsu (not specified)" },
        {   0x305, "Fujitsu (not specified)" },
        {   0x306, "Fujitsu (not specified)" },
        {   0x307, "Fujitsu (not specified)" },
        {   0x308, "Fujitsu (not specified)" },
        {   0x350, "Micronas Semiconductors, Inc. Development" },
        {   0x351, "Micronas Semiconductors, Inc. CELP833" },
        {   0x400, "Brooktree Digital" },
        {   0x401, "Intel Music Coder (IMC)" },
        {   0x402, "Ligos Indeo Audio" },
        {   0x450, "QDesign Music" },
        {   0x500, "On2 VP7 On2 Technologies" },
        {   0x501, "On2 VP6 On2 Technologies" },
        {   0x680, "AT&T VME VMPCM" },
        {   0x681, "AT&T TCP" },
        {   0x700, "YMPEG Alpha (dummy for MPEG-2 compressor)" },
        {   0x8ae, "ClearJump LiteWave (lossless)" },
        {   0x1000, "Olivetti GSM" },
        {   0x1001, "Olivetti ADPCM" },
        {   0x1002, "Olivetti CELP" },
        {   0x1003, "Olivetti SBC" },
        {   0x1004, "Olivetti OPR" },
        {   0x1100, "Lernout & Hauspie" },
        {   0x1101, "Lernout & Hauspie CELP codec" },
        {   0x1102, "Lernout & Hauspie SBC codec" },
        {   0x1103, "Lernout & Hauspie SBC codec" },
        {   0x1104, "Lernout & Hauspie SBC codec" },
        {   0x1400, "Norris Comm. Inc." },
        {   0x1401, "ISIAudio" },
        {   0x1500, "AT&T Soundspace Music Compression" },
        {   0x181c, "VoxWare RT24 speech codec" },
        {   0x181e, "Lucent elemedia AX24000P Music codec" },
        {   0x1971, "Sonic Foundry LOSSLESS" },
        {   0x1979, "Innings Telecom Inc. ADPCM" },
        {   0x1c07, "Lucent SX8300P speech codec" },
        {   0x1c0c, "Lucent SX5363S G.723 compliant codec" },
        {   0x1f03, "CUseeMe DigiTalk (ex-Rocwell)" },
        {   0x1fc4, "NCT Soft ALF2CD ACM" },
        {   0x2000, "FAST Multimedia DVM" },
        {   0x2001, "Dolby DTS (Digital Theater System)" },
        {   0x2002, "RealAudio 1 / 2 14.4" },
        {   0x2003, "RealAudio 1 / 2 28.8" },
        {   0x2004, "RealAudio G2 / 8 Cook (low bitrate)" },
        {   0x2005, "RealAudio 3 / 4 / 5 Music (DNET)" },
        {   0x2006, "RealAudio 10 AAC (RAAC)" },
        {   0x2007, "RealAudio 10 AAC+ (RACP)" },
        {   0x2500, "Reserved range to 0x2600 Microsoft" },
        {   0x3313, "makeAVIS (ffvfw fake AVI sound from AviSynth scripts)" },
        {   0x4143, "Divio MPEG-4 AAC audio" },
        {   0x4201, "Nokia adaptive multirate" },
        {   0x4243, "Divio G726 Divio, Inc." },
        {   0x434c, "LEAD Speech" },
        {   0x564c, "LEAD Vorbis" },
        {   0x5756, "WavPack Audio" },
        {   0x674f, "Ogg Vorbis (mode 1)" },
        {   0x6750, "Ogg Vorbis (mode 2)" },
        {   0x6751, "Ogg Vorbis (mode 3)" },
        {   0x676f, "Ogg Vorbis (mode 1+)" },
        {   0x6770, "Ogg Vorbis (mode 2+)" },
        {   0x6771, "Ogg Vorbis (mode 3+)" },
        {   0x7000, "3COM NBX 3Com Corporation" },
        {   0x706d, "FAAD AAC" },
        {   0x7a21, "GSM-AMR (CBR, no SID)" },
        {   0x7a22, "GSM-AMR (VBR, including SID)" },
        {   0xa100, "Comverse Infosys Ltd. G723 1" },
        {   0xa101, "Comverse Infosys Ltd. AVQSBC" },
        {   0xa102, "Comverse Infosys Ltd. OLDSBC" },
        {   0xa103, "Symbol Technologies G729A" },
        {   0xa104, "VoiceAge AMR WB VoiceAge Corporation" },
        {   0xa105, "Ingenient Technologies Inc. G726" },
        {   0xa106, "ISO/MPEG-4 advanced audio Coding" },
        {   0xa107, "Encore Software Ltd G726" },
        {   0xa109, "Speex ACM Codec xiph.org" },
        {   0xdfac, "DebugMode SonicFoundry Vegas FrameServer ACM Codec" },
        {   0xe708, "Unknown -" },
        {   0xf1ac, "Free Lossless Audio Codec FLAC" },
        {   0xfffe, "Extensible" },
        {   0xffff, "Development" }
    };

    bool equalsRiffTag(Exiv2::DataBuf& buf ,const char* str2) {
        for(int i=0;i<4;i++)
            if(toupper(buf.pData_[i])!=str2[i])
                return false;
        return true;
    }

    enum rifftags {
        container, filesize, filetype
    } ;
    enum streamTypeInfo {
        Audio,  MIDI, Text, Video
    };
    enum streamHeaderTags {
        codec = 1, sampleRate = 5, sampleCount = 8, quality = 10, sampleSize
    };
    enum bmptags {
        imageWidth, imageHeight, planes, bitDepth, compression, imageLength, pixelsPerMeterX, pixelsPerMeterY, numColors, numImportantColors
    };
    enum audioFormatTags {
        encoding, numberOfChannels, audioSampleRate, avgBytesPerSec = 4, bitsPerSample = 7
    };
    enum riffHdrlTags {
        IDIT, ISMP, LIST_odml, LIST_strl, avih
    };
    enum aviHeaderTags {
        frameRate, maxDataRate, frameCount = 4, streamCount = 6, imageWidth_h = 8, imageHeight_h
    };

    }

}

using namespace Exiv2::Internal;

namespace Exiv2 {

RiffVideo::RiffVideo(BasicIo::AutoPtr io)
        : Image(ImageType::riff, mdNone, io) {
} // RiffVideo::RiffVideo

std::string RiffVideo::mimeType() const {
    return "video/riff";
}

void RiffVideo::writeMetadata() {
}

void RiffVideo::readMetadata() {



    if (io_->open() != 0) throw Error(9, io_->path(), strError());

    // Ensure that this is the correct image type
    if (!isRiffType(*io_, false)) {
        if (io_->error() || io_->eof()) throw Error(14);
        throw Error(3, "RIFF");
    }

    IoCloser closer(*io_);
    clearMetadata();

    xmpData_["Xmp.video.fileSize"] = (double)io_->size()/(double)1048576;
    xmpData_["Xmp.video.fileName"] = io_->path();
    xmpData_["Xmp.video.mimeType"] = mimeType();

    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';

    for(long Counter = 0; Counter < 15000; Counter++) {
        std::memset(buf.pData_, 0x0, buf.size_);
        io_->read(buf.pData_, bufMinSize);

        if(equalsRiffTag(buf, "LIST") || equalsRiffTag(buf, "JUNK")) {
            if(equalsRiffTag(buf, "JUNK")) {
                junkHandler();
                std::cerr<<"\n";
                continue;
            }
            else
            listHandler();
        }

        switch(Counter) {
        case container:
            xmpData_["Xmp.video.container"] = buf.pData_;
            break;
        case filetype:
            xmpData_["Xmp.video.fileType"] = buf.pData_;
            break;
        case filesize:
            //long filesize_ = Exiv2::getULong(buf.pData_, littleEndian); (For Debug)
            //std::cerr <<std::setw(35)<<std::left<< "File Size Indicated By Metadata"<<": "<<filesize_<<" Bytes\n";
            break;
        }

    }
}

void RiffVideo::listHandler() {
    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';
    long chunkEndPosition;

    io_->read(buf.pData_, bufMinSize);
    chunkEndPosition = Exiv2::getULong(buf.pData_, littleEndian);

    for (positionCounter_ = 0; positionCounter_ <= chunkEndPosition; ) {
        std::memset(buf.pData_, 0x0, buf.size_);
        io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

        if(equalsRiffTag(buf, "LIST") || equalsRiffTag(buf, "JUNK")) {
            if(equalsRiffTag(buf, "JUNK")) {
                junkHandler();
                continue;
            }
            else
                listHandler();
        }
        else if(equalsRiffTag(buf, "HDRL")) {
            std::memset(buf.pData_, 0x0, buf.size_);
            io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

            if(equalsRiffTag(buf, "AVIH"))
                aviHeaderTagsHandler();
        }
        else if(equalsRiffTag(buf, "VIDS")) {
            streamHandler(Video);
        }
        else if(equalsRiffTag(buf, "AUDS")) {
            streamHandler(Audio);
        }
        else if(equalsRiffTag(buf, "INFO")) {
            infoTagsHandler();
        }
        else if(equalsRiffTag(buf, "MOVI")) {
            //std::cerr <<std::setw(35)<<std::left<< "Metadata Has Reached Its End"<<": "<<buf.pData_<<"\n"; (For Debug)
            return;
        }
    }
}

void RiffVideo::infoTagsHandler() { //Todo Decoding Info Tags
    const long bufMinSize = 100;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';
    long infoSize;

    io_->read(buf.pData_, 4); positionCounter_ += 4;
    std::cerr <<std::setw(35)<<std::left<< "Info Name"<<": "<< buf.pData_<<"\n";
    io_->read(buf.pData_, 4); positionCounter_ += 4;
    infoSize = Exiv2::getULong(buf.pData_, littleEndian);

    io_->read(buf.pData_, infoSize); positionCounter_ += infoSize;
    std::cerr <<std::setw(35)<<std::left<< "Info Data"<<": "<< buf.pData_<<"\n";
}

void RiffVideo::junkHandler() {
    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';
    long chunkEndPosition;
    Exiv2::Value::AutoPtr v = Exiv2::Value::create(Exiv2::xmpSeq);


    io_->read(buf.pData_, bufMinSize);
    chunkEndPosition = Exiv2::getULong(buf.pData_, littleEndian);

    //std::cerr <<std::setw(35)<<std::left<< "Junk Data"<<": ";   (For Debug)
    for (positionCounter_ = 0; positionCounter_ < chunkEndPosition; ){
        std::memset(buf.pData_, 0x0, buf.size_);
        if (chunkEndPosition - positionCounter_ < 4) {
            io_->read(buf.pData_, 2); positionCounter_ += 2;
        }
        else {
            io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
        }
        v->read(Exiv2::toString( buf.pData_));
    }
    xmpData_.add(Exiv2::XmpKey("Xmp.video.junk"), v.get());
}

void RiffVideo::aviHeaderTagsHandler() {
    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';
    long width = 0, height = 0, frame_count = 0;
    double frame_rate = 1;

    std::memset(buf.pData_, 0x0, buf.size_);
    io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

    for(int i = 0; i <= 9; i++, positionCounter_ += 4) {
        std::memset(buf.pData_, 0x0, buf.size_);
        io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

        switch(i) {
        case frameRate:
            xmpData_["Xmp.video.microSecPerFrame"] = Exiv2::getULong(buf.pData_, littleEndian);
            frame_rate = (double)1000000/(double)Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case (maxDataRate):
            xmpData_["Xmp.video.maxDataRate"] = (double)Exiv2::getULong(buf.pData_, littleEndian)/(double)1024;
            break;
        case frameCount:
            xmpData_["Xmp.video.frameCount"] = Exiv2::getULong(buf.pData_, littleEndian);
            frame_count = Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case streamCount:
            xmpData_["Xmp.video.streamCount"] = Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case imageWidth_h:
            width = Exiv2::getULong(buf.pData_, littleEndian);
            xmpData_["Xmp.video.width"] = width;
            break;
        case imageHeight_h:
            height = Exiv2::getULong(buf.pData_, littleEndian);
            xmpData_["Xmp.video.height"] = height;
            break;
        }
    }

    displayAspectRatio(width, height);

    Exiv2::XmpTextValue tv(Exiv2::toString(width));
        xmpData_.add(Exiv2::XmpKey("Xmp.video.frameSize/stDim:w"), &tv);
        tv.read(Exiv2::toString(height));
        xmpData_.add(Exiv2::XmpKey("Xmp.video.frameSize/stDim:h"), &tv);
        tv.read("pixels");
        xmpData_.add(Exiv2::XmpKey("Xmp.video.frameSize/stDim:unit"), &tv);

    displayDuration(frame_rate, frame_count);
}

void RiffVideo::streamHandler(int streamType) {
    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4]='\0';
    long divisor = 1;

    for(int i=1; i<=25; i++,positionCounter_++) {
        std::memset(buf.pData_, 0x0, buf.size_);
        io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

        switch(i) {
        case codec:
            if(streamType == Video)
                xmpData_["Xmp.video.videoCodec"] = buf.pData_;
            else if (streamType == Audio)
                xmpData_["Xmp.video.audioCodec"] = buf.pData_;
            else
                xmpData_["Xmp.video.codec"] = buf.pData_;
            break;
        case sampleRate:
            divisor=Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case (sampleRate+1):
            if(streamType == Video)
                xmpData_["Xmp.video.frameRate"] = returnSampleRate(buf,divisor);
            else if (streamType == Audio)
                xmpData_["Xmp.video.audioSampleRate"] = returnSampleRate(buf,divisor);
            else
                 xmpData_["Xmp.video.streamSampleRate"] = returnSampleRate(buf,divisor);
            break;
        case sampleCount:
            if(streamType == Video)
                xmpData_["Xmp.video.frameCount"] = Exiv2::getULong(buf.pData_, littleEndian);
            else if (streamType == Audio)
                xmpData_["Xmp.video.audioSampleCount"] = Exiv2::getULong(buf.pData_, littleEndian);
            else
                xmpData_["Xmp.video.streamSampleCount"] = Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case quality:
            if(streamType == Video)
                xmpData_["Xmp.video.videoQuality"] = Exiv2::getULong(buf.pData_, littleEndian);
            else if(streamType != Audio)
                xmpData_["Xmp.video.streamQuality"] = Exiv2::getULong(buf.pData_, littleEndian);
            break;
        case sampleSize:
            if(streamType == Video)
                xmpData_["Xmp.video.videoSampleSize"] = Exiv2::getULong(buf.pData_, littleEndian);
            else if(streamType != Audio)
                xmpData_["Xmp.video.streamSampleSize"] = Exiv2::getULong(buf.pData_, littleEndian);
            break;
        }

        if(equalsRiffTag(buf,"STRF")) {
            //std::cerr <<std::setw(35)<<std::left<< "Stream Format"<<": "<<"\n";  (For Debug)
            io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
            streamFormatHandler(streamType);
        }

        //Checks the end of Video Stream or Audio Stream and adds two bits to the buffer progress
        if(equalsRiffTag(buf,"VIDE")|| equalsRiffTag(buf,"AUDI")) {
            //if(equalsRiffTag(buf,"VIDE"))
            //    std::cerr <<std::setw(35)<<std::left<< "Stream Type"<<": "<<"Video Stream Ends\n";
            //if(equalsRiffTag(buf,"AUDI"))
            //    std::cerr <<std::setw(35)<<std::left<< "Stream Type"<<": "<<"Audio Stream Ends\n";  (For Debug)
            io_->read(buf.pData_, 2); positionCounter_ +=2;
            return;
        }
    }
}

void RiffVideo::streamFormatHandler(int streamType) {
    const long bufMinSize = 4;
    DataBuf buf(bufMinSize);
    buf.pData_[4] = '\0';

    if(streamType == Video) {
        io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;

        for(int i = 0; i <= 9; i++, positionCounter_++) {
            std::memset(buf.pData_, 0x0, buf.size_);

            switch(i) {
            case imageWidth: //Will be used in case of debugging
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                //std::cerr <<std::setw(35)<<std::left<< "Image Width"<<": "<<Exiv2::getULong(buf.pData_, littleEndian)<<"\n";
                break;
            case imageHeight: //Will be used in case of debugging
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                //std::cerr <<std::setw(35)<<std::left<< "Image Height"<<": "<<Exiv2::getULong(buf.pData_, littleEndian)<<"\n";
                break;
            case planes:
                io_->read(buf.pData_, 2); positionCounter_ += 2;
                xmpData_["Xmp.video.planes"] = Exiv2::getUShort(buf.pData_, littleEndian);
                break;
            case bitDepth:
                io_->read(buf.pData_, 2); positionCounter_ += 2;
                xmpData_["Xmp.video.pixelDepth"] = Exiv2::getUShort(buf.pData_, littleEndian);
                break;
            case compression:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                xmpData_["Xmp.video.compressor"] = buf.pData_;
                break;
            case imageLength:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                xmpData_["Xmp.video.imageLength"] = Exiv2::getULong(buf.pData_, littleEndian);
                break;
            case pixelsPerMeterX:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                xmpData_["Xmp.video.pixelPerMeterX"] = Exiv2::getULong(buf.pData_, littleEndian);
                break;
            case pixelsPerMeterY:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                xmpData_["Xmp.video.pixelPerMeterY"] = Exiv2::getULong(buf.pData_, littleEndian);
                break;
            case numColors:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                if(Exiv2::getULong(buf.pData_, littleEndian) == 0)
                    xmpData_["Xmp.video.numOfColours"] = "Unspecified";
                else
                    xmpData_["Xmp.video.numOfColours"] = Exiv2::getULong(buf.pData_, littleEndian);
                break;
            case numImportantColors:
                io_->read(buf.pData_, bufMinSize); positionCounter_ += 4;
                if(Exiv2::getULong(buf.pData_, littleEndian) == 0)
                    xmpData_["Xmp.video.numOfImpColours"] = "All";
                else
                    xmpData_["Xmp.video.numIfImpColours"] = Exiv2::getULong(buf.pData_, littleEndian);
                break;
            }
        }
    }
    else if(streamType == Audio) {
        int c = 0;
        const TagDetails* td;

        for(int i = 0; i <= 7; i++, positionCounter_++) {
            io_->read(buf.pData_, 2); positionCounter_ += 2;

            switch(i) {
            case encoding:
                td = find(audioEncodingValues , Exiv2::getUShort(buf.pData_, littleEndian));
                if(td)
                    xmpData_["Xmp.video.audioCompressor"] = exvGettext(td->label_);
                else
                    xmpData_["Xmp.video.audioCompressor"] = Exiv2::getUShort(buf.pData_, littleEndian);
                break;
            case numberOfChannels:
                c = Exiv2::getUShort(buf.pData_, littleEndian);
                if(c == 1) xmpData_["Xmp.video.audioChannelType"] = "Mono";
                else if(c == 2) xmpData_["Xmp.video.audioChannelType"] = "Stereo";
                else if(c == 5) xmpData_["Xmp.video.audioChannelType"] = "5.1 Surround Sound";
                else if(c == 7) xmpData_["Xmp.video.audioChannelType"] = "7.1 Surround Sound";
                else xmpData_["Xmp.video.audioChannelType"] = "Mono";
                break;
            case audioSampleRate:
                xmpData_["Xmp.video.audioSampleRate"] = Exiv2::getUShort(buf.pData_, littleEndian);
                break;
            case avgBytesPerSec:
                xmpData_["Xmp.video.audioSampleType"] = Exiv2::getUShort(buf.pData_, littleEndian);
                break;
            case bitsPerSample:
                xmpData_["Xmp.video.bitsPerSample"] = Exiv2::getUShort(buf.pData_,littleEndian);
                io_->read(buf.pData_, 2); positionCounter_ += 2;
                break;
            }
        }
    }
}

double RiffVideo::returnSampleRate(Exiv2::DataBuf& buf, long divisor) {
    return ((double)Exiv2::getULong(buf.pData_, littleEndian) / (double)divisor);
}

void RiffVideo::displayAspectRatio(long width, long height) {
    double aspectRatio = (double)width / (double)height;
    aspectRatio = floor(aspectRatio*10) / 10;
    if(aspectRatio == 1.3) xmpData_["Xmp.video.aspectRatio"] = "4:3";
    else if(aspectRatio == 1.7) xmpData_["Xmp.video.aspectRatio"] = "16:9";
    else if(aspectRatio == 1.0) xmpData_["Xmp.video.aspectRatio"] = "1:1";
    else if(aspectRatio == 1.6) xmpData_["Xmp.video.aspectRatio"] = "16:10";
    else if(aspectRatio == 2.2) xmpData_["Xmp.video.aspectRatio"] = "2.21:1";
    else if(aspectRatio == 2.3) xmpData_["Xmp.video.aspectRatio"] = "2.35:1";
    else if(aspectRatio == 1.2) xmpData_["Xmp.video.aspectRatio"] = "5:4";
    else xmpData_["Xmp.video.aspectRatio"] = aspectRatio;
}

void RiffVideo::displayDuration(double frame_rate, long frame_count) {
    if(frame_rate == 0)
        return;

    long duration = frame_count / frame_rate;
    xmpData_["Xmp.video.fileDataRate"] = (double)io_->size()/(double)(1048576*duration);
    xmpData_["Xmp.video.duration"] = duration; //Duration in number of seconds
}

Image::AutoPtr newRiffInstance(BasicIo::AutoPtr io, bool /*create*/) {
    Image::AutoPtr image(new RiffVideo(io));
    if (!image->good()) {
        image.reset();
    }
    return image;
}

bool isRiffType(BasicIo& iIo, bool advance) {
    const int32_t len = 2;
    const unsigned char RiffVideoId[4] = { 'R', 'I', 'F' ,'F'};
    byte buf[len];
    iIo.read(buf, len);
    if (iIo.error() || iIo.eof()) {
        return false;
    }
    bool matched = (memcmp(buf, RiffVideoId, len) == 0);
    if (!advance || !matched) {
        iIo.seek(-len, BasicIo::cur);
    }
    return matched;
}

}