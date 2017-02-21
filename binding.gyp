
{
  	"targets": [
		{
	    	"target_name": "bridge",
	    	'include_dirs': ['include', 'include/calculator', 'include/phast', 'include/psat', '../cmake-build-debug/bin/test_db.sql',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'src/bindings/bridge.cpp',
			],
			"conditions": [
		    	[ 'OS=="mac"', {
		    	    'libraries': [
                        '../cmake-build-debug/lib/libamo_tools_suite.a'
		    	    ],
   		           	"xcode_settings": {
   					    'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++'],
                        #'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                        'OTHER_LDFLAGS': ['-stdlib=libc++'],
                        # 'MACOSX_DEPLOYMENT_TARGET': '10.9'
                    }
				}]
	       	]
	    }
	]
}