
{
  	"targets": [
		{
	    	"target_name": "bridge",
	    	'include_dirs': ['include', 'include/calculator', 'include/phast', 'include/psat', 'include/sqlite', 'third_party/sqlite',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'src/bindings/bridge.cpp',
				'src/bindings/losses.cpp',
			],
			"conditions": [
		    	[ 'OS=="mac"', {
				"link_settings": {
					'libraries': ['../lib/libamo_tools_suite.a'],
				},
   		           	"xcode_settings": {
   					    #'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++'],
                        'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                        'OTHER_LDFLAGS': ['-stdlib=libc++'],
                        # 'MACOSX_DEPLOYMENT_TARGET': '10.9'
                    },
				}],
			[ 'OS=="linux"', {
				"link_settings": {
					'libraries': ['../lib/libamo_tools_suite.a'],
				},
				"cflags": ["-std=c++11"],
			}],
			[ 'OS=="win"', {
				"link_settings": {
					'libraries': ['../build/Release/obj/bridge.lib'],
					}
			}]
					
	       	]
	    }
	]
}
