
{
  	"targets": [
		{
	    	"target_name": "bridge",
	    	'include_dirs': ['include', 'include/calculator', 'include/phast', 'include/psat', 'include/sqlite',
	    	    "<!(node -e \"require('nan')\")"
	    	 ],
			'sources' : [
				'src/bindings/bridge.cpp',
				"<!@(node -e \"console.log(require('fs').readdirSync('src/').map(f=>'src/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/calculator/').map(f=>'src/calculator/'+f).join(' '))\")",
				"<!@(node -e \"console.log(require('fs').readdirSync('src/psat/').map(f=>'src/psat/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/phast/').map(f=>'src/phast/'+f).join(' '))\")",
                "<!@(node -e \"console.log(require('fs').readdirSync('src/sqlite/').map(f=>'src/sqlite/'+f).join(' '))\")"
			],
			"conditions": [
		    	[ 'OS=="mac"', {
   		           	"xcode_settings": {
   					    #'OTHER_CPLUSPLUSFLAGS' : ['-stdlib=libc++'],
                        'OTHER_CPLUSPLUSFLAGS' : ['-std=c++11','-stdlib=libc++'],
                        'OTHER_LDFLAGS': ['-stdlib=libc++'],
                        # 'MACOSX_DEPLOYMENT_TARGET': '10.9'
                    }
				}]
	       	]
	    }
	]
}